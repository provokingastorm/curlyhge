#ifndef CurlyCore_H_
#define CurlyCore_H_

// ----------------------------------------------------------------------------
// Cleanup macros
// ----------------------------------------------------------------------------

#define SAFE_DELETE(ptr) { if(ptr) { delete ptr; ptr = NULL; } }

#define SAFE_DELETE_ARRAY(arr) { if(arr) { delete[] arr; arr = NULL;} }

#define SAFE_SHUTDOWN(ptr) { if(ptr) { ptr->Shutdown(); ptr = NULL;} }

#define SAFE_DELETE_STL_VECTOR(stl_vector) \
{ \
	for(unsigned int _STLVectorIndex = 0; _STLVectorIndex < stl_vector.size(); ++_STLVectorIndex) \
	{ \
		delete stl_vector[_STLVectorIndex]; \
	} \
	stl_vector.~vector(); \
}

// ----------------------------------------------------------------------------
// String utilities
// ----------------------------------------------------------------------------

char* ChzStrDuplicate(const char* SrcString);
char* ChzStrLower(const char* SrcString);


int MaxInt(int First, int Second);
float MaxFloat(float First, float Second);

int MinInt(int First, int Second);
float MinFloat(float First, float Second);

#endif

// EOF
