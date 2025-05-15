

#ifndef _SERIALIZER
#define _SERIALIZER

#include "CustomTypeTraits.hpp"

// Forward declarations
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
 * The principle of operation of this class is based on:
 * - Using std::enable_if and (custom) type traits to allow proper object type resolution during the compile time.
 * - Using double dispatch thanks to the ObjectSerializer() class that dispatches the calls to the relevant ObjectSerializer::addPropertyImpl
 *		methods. These calls may resolve back to Serializable::serialize methods if the class is something else than the primitive type.
 * - Using this approach we can use dynamic polymorphism to inherit from ObjectSerializer class, and static polymorphism, i.e. templates, to
 *      resolve all types properly.
 *
 * addProperty() methods are used to resolve the types properly and allow creating nested objects. These and addValue() methods
 *		are heavily templated in order to resolve all possible types correctly. This makes the API extremly easy to use by only calling
 *		ObjectSerializer::addProperty() method and entire complicated logic is hidden inside of ObjectSerializer.
 * addValue() methods are used to pass the value to be serialized or to dispatch it back to addProperty() if it cannot be resolved yet.
 * startObject() endObject() startArray() endArray() startPrimitive() endPrimitive() are used to create proper serialized structure
 *		that should be adapted to different data standards.
 *
 * For type traits and helpers please refer to `CustomTypeTraits.hpp`.
 *
 * @see Serializable
 */
class ObjectSerializer
{
public:
	template<typename T>
	void addProperty(const std::string &name, const T &value)
	{
		_addProperty(value, name);
	}

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

	// clang-format off

private:
	/* *************** */
	/*   ADD_PROPERTY  */
	/* *************** */
	//	Add some new property, can be primitive, Serializable, map/container of maps, pair, container

	// Primitive or string pointer
	template<typename T>
	typename std::enable_if_t<(!is_Serializable<T>::value 
		&& !is_pair<T>::value 
		&& !is_any_pointer<T>::value
		&& !std::is_array_v<T>
		&& !is_sparse<T>::value
		&& ((is_iterable_container<T>::value && is_string<T>::value) || !is_iterable_container<T>::value))
		||
		(!is_Serializable<T>::value
		&& is_any_pointer<T>::value
		&& is_string<T>::value)
	>
		_addProperty(const T &value, const std::string &name = std::string())
	{
		startPrimitive(name);
		addValue(value);
		endPrimitive();
	}
	// Primitive - std::to_string<E> needs to be valid
	template<typename T, typename E>
	typename std::enable_if_t<has_std_to_string<E>::value>
		_addProperty(const T &value, const E &name)
	{
		startPrimitive(std::to_string(name));
		addValue(value);
		endPrimitive();
	}

	// Other pointer
	template<typename T>
	typename std::enable_if_t<is_any_pointer<T>::value && !is_string<T>::value>
		_addProperty(const T &value, const std::string &name = std::string())
	{
		if(value)
			_addProperty(*value, name);
	}
	// Serializable class
	template<typename T>
	typename std::enable_if_t<is_Serializable<T>::value>
		_addProperty(const T &o, const std::string &name = std::string())
	{
		startObject(name);
		to_ptr(o)->serialize(*this);
		endObject();
	}
	//// Container
	template<typename T>
	typename std::enable_if_t<(!is_string<T>::value && is_iterable_container<T>::value) || std::is_array_v<T> || is_sparse<T>::value>
		_addProperty(const T &value, const std::string &name = std::string())
	{
		startArray(name);
		addValue(value);
		endArray();
	}
	// Pair
	template<typename T>
	typename std::enable_if_t<is_pair<T>::value>
		_addProperty(const T &value, const std::string &name = std::string())
	{
		startObject(name);
		addValue(value);
		endObject();
	}

	/* ************** */
	/*    ADD_VALUE   */
	/* ************** */
	// Helpers to dispatch the types based on the current and nested-types (if present, pair or containers)

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
		_addProperty(p.second, p.first);
	}

	// If container of: containers or Serializables or pointers
	template<typename T>
	typename std::enable_if_t<
		is_iterable_container<T>::value 
		&& (is_iterable_container<typename T::value_type>::value 
			|| is_Serializable<typename T::value_type>::value
			|| is_any_pointer<typename T::value_type>::value)
	>
		addValue(const T &container)
	{
		for (const auto &t : container)
			_addProperty(t);
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

	// External types support
	// if (external lib) tree
	template<typename T, class tree_node_allocator>
	void addValue(const peka::tree<T, tree_node_allocator> &tree)
	{
		auto pos = tree.begin();
		while (pos != tree.end())
		{
			_addProperty(pos.node->data);
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
				_addProperty(row);
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

/**
* The class to be inherited from if serialization is to be supported.
*
* @see ObjectSerializer
*/
class Serializable
{
public:
	virtual void serialize(ObjectSerializer &obj) const = 0;
};

#endif
