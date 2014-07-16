#include "precompiledHeaders.h"
#include "RecentlyClosedFiles.h"

RecentlyClosedFiles::RecentlyClosedFiles() :
	_maxSize(100)
{
}

RecentlyClosedFiles::RecentlyClosedFiles(int maxSize) :
	_maxSize(maxSize) 
{
}

RecentlyClosedFiles::~RecentlyClosedFiles()
{
	_files.clear();
}

bool RecentlyClosedFiles::add(const sessionFileInfo &fileInfo)
{
	deque<sessionFileInfo>::iterator removePos = _inDeque(fileInfo._fileName);
	bool remove = (removePos != _files.end());

	if (remove) {
		_files.erase(removePos);
	}
	
	_files.push_back(fileInfo);

	if (_files.size() > _maxSize) {
		_files.pop_front();
	}

	return (remove == true ? false : true);
}

bool RecentlyClosedFiles::remove(const sessionFileInfo &fileInfo)
{
	deque<sessionFileInfo>::iterator removePos = _inDeque(fileInfo._fileName);
	if (removePos != _files.end()) {
		_files.erase(removePos);
		return true;
	}
	return false;
}

void RecentlyClosedFiles::clear()
{
	_files.clear();
}

bool RecentlyClosedFiles::get(const generic_string &fileName, sessionFileInfo &fileInfo)
{
	deque<sessionFileInfo>::iterator fileNamePos = _inDeque(fileName);

	if (fileNamePos != _files.end()) {
		fileInfo = *fileNamePos;
	}
	return (fileNamePos != _files.end());
}

deque<sessionFileInfo>::iterator RecentlyClosedFiles::_inDeque(const generic_string &fileName)
{
	deque<sessionFileInfo>::iterator iter = _files.begin();
	for (; iter != _files.end(); ++iter)
	{
		if ((*iter)._fileName == fileName) {
			break;
		}
	}
	return iter;
}

const sessionFileInfo &RecentlyClosedFiles::get(size_t idx) const
{
	return _files.at(idx);
}