// vim: set noexpandtab tabstop=2:

#pragma once

template <typename T>
T* constVoid2localType(const void * ptr)
{
	return const_cast<T*>(
			static_cast<const T*>(ptr)
			);
}
