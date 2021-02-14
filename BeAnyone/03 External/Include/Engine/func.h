#pragma once

void TestInit();

void TestUpdate();

void TestRender();

void TestRelease();

int GetSizeofFormat(DXGI_FORMAT _eFormat);

template<class T, int iSize>
void Safe_Delete_arr( T( &arr )[iSize] ) 
{
	for (int i = 0; i < iSize; ++i)
	{
		SAFE_DELETE( arr[i] );
	}
}