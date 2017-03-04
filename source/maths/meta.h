#pragma once

#define TEMPLATE_IMPLEMENT_PRIMITIVE_TYPES(x)	\
template class x<bool>;\
template class x<char>;\
template class x<int>;\
template class x<float>;\
template class x<double>;\
template class x<void>;\
template class x<wchar_t>;

#define TEMPLATE_IMPLEMENT_MATHEMATICAL_TYPES(x)\
template class x<char>;\
template class x<int>;\
template class x<short int>;\
template class x<long int>;\
template class x<long long int>;\
template class x<unsigned char>;\
template class x<unsigned int>;\
template class x<unsigned short int>;\
template class x<unsigned long int>;\
template class x<unsigned long long int>;\
template class x<float>;\
template class x<double>;\
template class x<double long>
