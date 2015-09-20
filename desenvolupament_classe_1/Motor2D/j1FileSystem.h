#ifndef _J1FILESYSTEM_H__
#define _J1FILESYSTEM_H__
#include "SDL/include/sdl.h"
#include "SDL_image\include\SDL_image.h"
#include "PhysFS\include\physfs.h"
#include "j1Module.h"

#pragma comment (lib,"PhysFs/libx86/physfs.lib")

class j1FileSystem : public j1Module
{
public:
	j1FileSystem();
	~j1FileSystem();


	bool Awake();
	bool CleanUp();

	bool OpenFile(const char* file);
	bool LoadImagefromBuffer(const char* file);

private:
	Sint64  file_lenght;
	void* file_data;

};


#endif // !_J1FILESYSTEM_H__