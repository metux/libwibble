#ifndef WIBBLE_SYS_DIRECTORY_H
#define WIBBLE_SYS_DIRECTORY_H

#include <string>
#include <dirent.h>		// opendir, closedir
#include <memory>		// auto_ptr

struct stat;

namespace wibble {
namespace sys {
namespace fs {

/**
 * stat() the given file and return the struct stat with the results.
 * If the file does not exist, return NULL.
 * Raises exceptions in case of errors.
 */
std::auto_ptr<struct stat> stat(const std::string& pathname);

/// access() a filename
bool access(const std::string &s, int m);

/// Create the given directory, if it does not already exists.
/// It will complain if the given pathname already exists but is not a
/// directory.
void mkdirIfMissing(const std::string& dir, mode_t mode);

/// Create all the component of the given directory, including the directory
/// itself.
void mkpath(const std::string& dir);

/// Ensure that the path to the given file exists, creating it if it does not.
/// The file itself will not get created.
void mkFilePath(const std::string& file);

/// Nicely wrap access to directories
class Directory
{
	std::string m_path;

public:
	class const_iterator
	{
		DIR* dir;
		struct dirent* d;

	public:
		// Create an end iterator
		const_iterator() : dir(0), d(0) {}
		// Create a begin iterator
		const_iterator(DIR* dir) : dir(dir), d(0) { ++(*this); }
		// Cleanup properly
		~const_iterator() { if (dir) closedir(dir); }

		// auto_ptr style copy semantics
		const_iterator(const const_iterator& i)
		{
			dir = i.dir;
			d = i.d;
			const_iterator* wi = const_cast<const_iterator*>(&i);
			wi->dir = 0;
			wi->d = 0;
		}
		const_iterator& operator=(const const_iterator& i)
		{
			// Catch a = a
			if (&i == this) return *this;
			if (dir) closedir(dir);
			dir = i.dir;
			d = i.d;
			const_iterator* wi = const_cast<const_iterator*>(&i);
			wi->dir = 0;
			wi->d = 0;
		}

		const_iterator& operator++()
		{
			if ((d = readdir(dir)) == 0)
			{
				closedir(dir);
				dir = 0;
			}
			return *this;
		}

		std::string operator*() { return d->d_name; }
		struct dirent* operator->() { return d; }

		bool operator==(const const_iterator& iter) const
		{
			return dir == iter.dir && d == iter.d;
		}
		bool operator!=(const const_iterator& iter) const
		{
			return dir != iter.dir || d != iter.d;
		}
	};

	Directory(const std::string& path) : m_path(path) {}

	/// Pathname of the directory
	const std::string& path() const { return m_path; }

	/// Check that the directory exists and is a directory
	bool valid();

	/// Begin iterator
	const_iterator begin();

	/// End iterator
	const_iterator end() const;
};

}
}
}

// vim:set ts=4 sw=4:
#endif