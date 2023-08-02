/*
© Copyright CERN 2023. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef _SERIALIZER
#define _SERIALIZER

#include "CustomTypeTraits.hpp"

class Serializable;
// forward declaration for peka::tree external library
namespace peka
{
template<class T, class tree_node_allocator>
class tree;
}; // namespace peka

// forward declaration for Eigen::matrix external library
namespace Eigen
{
template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
class Matrix;

template<typename Scalar, int Options, typename Index>
class SparseMatrix;
} // namespace Eigen

/**
 * Abstract class featuring Serialization.
 *
 * To use this class, you should override all the virtual methods.
 *
 * The  principle of operation of this class can be explained with two concepts:
 * - Using std::enable_if and (custom) type traits to allow proper object type resolution during the compile time.
 * - Using double dispatch thanks to inner @SerializerObject::SerializationHelper class that dispatches the calls to the
 *		relevant @SerializerObject::addProperty methods, some of which are virtual. This enables to use dynamic (inheritance)
 *		and static (templates) polymorphism at the same time. Then @addProperty methods may dispatch it back to @addProperty
 *		methods or to @addValue methods.
 *
 * @addProperty methods are used to resolve the types properly and allow creating nested objects. These and @addValue methods
 *		are heavily templated in order to resolve all possible types correctly. This makes the API extremly easy to use by only calling
 *		@SerializerObject::SerializationHelper::addProperty method and entire complicated logic is hidden inside of @SerializerObject.
 * @addValue methods are used to pass the value to be serialized or to dispatch it back to @addProperty if it cannot be resolved yet
 * @startObject @endObject @startArray @endArray @startPrimitive @endPrimitive are used to create proper serialized structure
 *		that should be adapted to different serialization standards.
 *
 * For type traits and helpers please refer to `CustomTypeTraits.hpp`.
 */
class SerializerObject
{
public:
	/**
	 * Helper class that is utilizing both dynamic and static polymorphism, it allows to call virtual @addProperty methods
	 * of @SerializerObject with a templated argument using @SerializerObject::SerializationHelper::addProperty.
	 */
	class SerializationHelper
	{
	public:
		/**
		 * Empty constructor
		 *
		 * @param @ser holds the SerializerObject used for serialization.
		 */
		SerializationHelper(SerializerObject &ser) : ser(ser) {}
		/**
		 * Empty destructor.
		 */
		~SerializationHelper() = default;

		/**
		 * Calls @addProperty methods of @SerializerObject with a templated argument
		 *
		 * @param name of the object
		 * @param ser SerializerObject used for serialization
		 */
		template<typename T>
		void addProperty(const std::string &name, const T &value)
		{
			ser.addProperty(value, name);
		}

	protected:
		SerializerObject &ser;
	};

public:
	/**
	 * Creates a new @SerializerObject::SerializationHelper object that should be shared by all the classes writing to the same instance.
	 *
	 * Even though the @SerializationHelper object is new each time on @SerializerObject::getSerializationHelper call, it takes the current
	 * @SerializerObject as a constructor argument so the write always goes to the same serialized object.
	 */
	SerializationHelper getSerializationHelper() { return SerializationHelper(*this); }
	/**
	 * Get string representation of the serialized contents. The returned JSON should be in UTF-8 format.
	 */
	virtual std::string getStringRepresentation() = 0;

protected:
	// Virtual functions
	// structure related
	virtual void startObject(const std::string &name) = 0;
	virtual void startObject() = 0;
	virtual void endObject() = 0;
	virtual void startArray(const std::string &name) = 0;
	virtual void startArray() = 0;
	virtual void endArray() = 0;
	virtual void startPrimitive(const std::string &name) = 0;
	virtual void endPrimitive() = 0;

	/* *************** */
	/*   ADD_PROPERTY  */
	/* *************** */
	//	Add some new property, can be primitive, Serializable, map/container of maps, pair, container

	// clang-format off

	// Primitive - !Serializable && !pair && !pointer && !c-style-array && !sparce-matrix && ((container && is_string) || !container))
	template<typename T>
	typename std::enable_if_t<!is_Serializable<T>::value 
		&& !is_pair<T>::value 
		&& !is_any_pointer<T>::value
		&& !std::is_array_v<T>
		&& !is_sparse<T>::value
		&& ((is_iterable_container<T>::value && is_string<T>::value) 
			|| !is_iterable_container<T>::value)
	>
		addProperty(const T &value, const std::string &name = std::string())
	{
		startPrimitive(name);
		addValue(value);
		endPrimitive();
	}
	// Primitive - std::to_string<E> needs to be valid
	template<typename T, typename E>
	auto addProperty(const T &value, const E &name) -> decltype(std::to_string(name), void())
	{
		startPrimitive(std::to_string(name));
		addValue(value);
		endPrimitive();
	}

	// String pointers - is_any_pointer && is_string
	template<typename T>
	typename std::enable_if_t<!is_Serializable<T>::value && is_any_pointer<T>::value && is_string<T>::value>
		addProperty(const T &value, const std::string &name = std::string())
	{
		startPrimitive(name);
		addValue(value);
		endPrimitive();
	}
	// Other pointers
	template<typename T>
	typename std::enable_if_t<is_any_pointer<T>::value && !is_string<T>::value>
		addProperty(const T &value, const std::string &name = std::string())
	{
		if(value)
			addProperty(*value, name);
	}
	// Serializable class
	template<typename T>
	typename std::enable_if_t<is_Serializable<T>::value>
		addProperty(const T &o, const std::string &name = std::string())
	{
		startObject(name);
		SerializerObject::SerializationHelper serHelper = getSerializationHelper();
		to_ptr(o)->serialize(serHelper);
		endObject();
	}
	//// Container
	template<typename T>
	typename std::enable_if_t<(!is_string<T>::value && is_iterable_container<T>::value) || std::is_array_v<T> || is_sparse<T>::value>
		addProperty(const T &value, const std::string &name = std::string())
	{
		startArray(name);
		addValue(value);
		endArray();
	}
	// Pair
	template<typename T>
	typename std::enable_if_t<is_pair<T>::value>
		addProperty(const T &value, const std::string &name = std::string())
	{
		startObject(name);
		addValue(value);
		endObject();
	}

	/* ************** */
	/*    ADD_VALUE   */
	/* ************** */
	// Helpers to dispatch the types based on the current and nestey-types (if present, pair or containers)

	// primitive value related
	virtual void addValue(int value) = 0;
	virtual void addValue(double value) = 0;
	virtual void addValue(float value) = 0;
	virtual void addValue(char value) = 0;
	virtual void addValue(wchar_t value) = 0;
	virtual void addValue(bool value) = 0;
	virtual void addValue(const std::string &value) = 0;
	virtual void addValue(const char *value) = 0;

	// If pair
	template<typename K, typename V>
	void addValue(const std::pair<K, V> &p)
	{
		addProperty(p.second, p.first);
	}

	// If container of containers or Serializables
	template<typename T>
	typename std::enable_if_t<
		is_iterable_container<T>::value 
		&& (is_iterable_container<typename T::value_type>::value 
			|| is_Serializable<typename T::value_type>::value)
	>
		addValue(const T &container)
	{
		for (const auto &t : container)
			addProperty(t);
	}

	// if container of pointers
	template<typename T>
	typename std::enable_if_t<
		is_iterable_container<T>::value 
		&& is_any_pointer<typename T::value_type>::value 
	>
		addValue(const T &container)
	{
		for (const auto &t : container)
			addProperty(t);
			return;
	}

	// If container of primitives
	template<typename T>
	typename std::enable_if_t<
		is_iterable_container<T>::value 
		&& !is_iterable_container<typename T::value_type>::value 
		&& !is_Serializable<typename T::value_type>::value
		&& !is_any_pointer<typename T::value_type>::value
	>
		addValue(const T &container)
	{
		for (const auto &t : container)
			addValue(t);
	}

	// if C-style array
	template<typename T>
	std::enable_if_t<std::is_array_v<T>> 
		addValue(const T &container)
	{
		for (const auto &t : container)
			addValue(t);
	}

	// if (external lib) tree
	template<typename T, class tree_node_allocator>
	void addValue(const peka::tree<T, tree_node_allocator> &tree)
	{
		auto pos = tree.begin();
		while (pos != tree.end())
		{
			addProperty(pos.node->data);
			pos++;
		}
	}

	// if (external lib) Eigen (Dense) // Can be matrices or vectors
	template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
	void addValue(const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols> &matrix)
	{
		// Column Vector
		if(matrix.cols() == 1)
			addValue(*(matrix.colwise().begin()));
		// Matrix
		else
		{
			for (auto row : matrix.rowwise())
				addProperty(row);
		}
	}

	// if (external lib) Eigen (Sparse)
	template<typename Scalar, int Options, typename Index>
	void addValue(const Eigen::SparseMatrix<Scalar, Options, Index> &matrix)
	{
		addValue(matrix.toDense());
	}
};

// clang-format on

class Serializable
{
public:
	virtual void serialize(SerializerObject::SerializationHelper &obj) const = 0;
};

#endif
