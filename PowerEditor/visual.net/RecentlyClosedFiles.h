#ifndef RECCLOSEDFILES_H
#define RECCLOSEDFILES_H

// Global includes
#include <windows.h>
#include <set>

// Local includes
#ifndef PARAMETERS_H
#include "Parameters.h"
#endif

class RecentlyClosedFiles
{
public:
	RecentlyClosedFiles();

	~RecentlyClosedFiles();
	
	// If element already existed function replaces it by new fileInfo
	// however returning false
	bool add(const sessionFileInfo &fileInfo);
	bool remove(const sessionFileInfo &fileInfo);
	void clear();
	// Get whole file info by file name
	// result is stored in fileInfo if function returns true
	// false is returned in case of file not found
	bool get(const generic_string &fileName, sessionFileInfo &fileInfo);

private :
	typedef set <sessionFileInfo, 
				bool(*)(sessionFileInfo, sessionFileInfo)>::iterator setIterator;

	set <sessionFileInfo, bool (*)(sessionFileInfo, sessionFileInfo)> _files;

	// Compares only _fileName
	static bool _cmpFiles(sessionFileInfo f1, sessionFileInfo f2);
};

#endif //RECCLOSEDFILES_H