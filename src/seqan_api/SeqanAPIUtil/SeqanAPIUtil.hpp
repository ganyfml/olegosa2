// vim: set noexpandtab tabstop=2:

#pragma once

//FIXME indentation
	template <typename Type>
Type* constVoid2localType(const void * ptr)
{
	return const_cast<Type*>(
			static_cast<const Type*>(ptr)
			);
}
