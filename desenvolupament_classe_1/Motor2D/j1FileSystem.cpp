#include "j1FileSystem.h"
#include "p2Log.h"


j1FileSystem::j1FileSystem() : j1Module(){}
j1FileSystem::~j1FileSystem(){}

bool j1FileSystem::Awake()
{
	bool ret = true;
	LOG("Initializing");
	if (PHYSFS_init(NULL) == 0)
	{
		ret = false;
		LOG("Failed to initialize ERROR:%s\n", PHYSFS_getLastError());
	}

	return ret;
}

bool j1FileSystem::CleanUp()
{
	bool ret = true;
	if (PHYSFS_deinit() == 0)
	{
		ret = false;
		LOG("Failed to cleanup. ERROR:%s\n", PHYSFS_getLastError());
	}

	return ret;
}

bool j1FileSystem::OpenFile(const char* file)
{
	if (0 == PHYSFS_exists(file))
	{
		return false; //file doesn't exist
	}

	PHYSFS_file* myfile = PHYSFS_openRead(file);

	// Get the lenght of the file
	file_lenght = PHYSFS_fileLength(myfile);

	// Get the file data.
	file_data = new Uint32[file_lenght];

	int length_read = PHYSFS_read(myfile, file_data, 1, file_lenght);

	if (length_read != (int)file_lenght)
	{
		delete[] file_data;
		file_data = 0;
		return false;
	}

	PHYSFS_close(myfile);


	return true;
}

bool j1FileSystem::LoadImagefromBuffer(const char* file)
{
	OpenFile(file);

	SDL_RWops *rw = SDL_RWFromMem(file_data, file_lenght);

	SDL_Surface* surface = IMG_Load_RW(rw, 0);

	SDL_FreeRW(rw);

	return true;
}


