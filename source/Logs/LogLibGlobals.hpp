#if !defined(__linux__) && defined(SUGL_SHARED)
	#if defined(UIPlugins_EXPORT)
		# define SUGL_SHARED_EXPORT __declspec(dllexport)
	#else
		# define SUGL_SHARED_EXPORT __declspec(dllimport)
	#endif
#endif // #ifndef __linux__

#ifndef SUGL_SHARED_EXPORT
	# define SUGL_SHARED_EXPORT
#endif
