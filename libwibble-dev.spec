Summary: Library of various useful C++ code
Name: libwibble-dev
Version: 0.1.28.1.1
Release: 1
License: BSD
Group: Development/Libraries
URL: http://packages.qa.debian.org/libwibble
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
BuildRequires: cmake, doxygen, libtool, boost-devel
Requires: boost-devel

 
%description
 libwibble collects the foundation code that has been used over time
 in various C++ projects by Peter Rockai and Enrico Zini, so that it can
 be maintained properly and in a single place.
 .
 The library contains:
  * an exception hierarchy;
  * various useful mixin classes;
  * shortcuts for set operations;
  * a commandline parser that supports cvs-style subcommands;
  * improved macros for tut unit testing;
  * a non-intrusive polimorphic envelope.

%prep
%setup -q

%build
%cmake -DHAVE_TUT=ON
make
#make check

%install
[ "%{buildroot}" != / ] && rm -rf "%{buildroot}"
make install DESTDIR="%{buildroot}"

%clean
[ "%{buildroot}" != / ] && rm -rf "%{buildroot}"

%files
%defattr(-,root,root,-)
/usr/lib
/usr/include
/usr/lib/pkgconfig/libwibble*
/usr/share/aclocal/libwibble*.m4
/usr/bin/wibble-test-genrunner
/usr/share/man/man1/wibble-test-genrunner.1.gz
/usr/share/wibble/test.cmake
#%doc /usr/share/doc/libwibble-dev

%post
/sbin/ldconfig

%postun
/sbin/ldconfig


%changelog
* Wed Sep 19 2007 Enrico Zini <enrico@enricozini.org>
- Initial build.
