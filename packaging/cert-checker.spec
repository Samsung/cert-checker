Name:       cert-checker
Summary:    OCSP checking on application installation
Version:    0.0.1
Release:    1
Group:      System/Security
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires: cmake
BuildRequires: zip
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(capi-appfw-package-manager)
BuildRequires: pkgconfig(notification)
BuildRequires: pkgconfig(dbus-1)
BuildRequires: pkgconfig(dbus-glib-1)
BuildRequires: pkgconfig(libsystemd-journal)

%description
Cert-checker

%prep
%setup -q

%build
export CFLAGS="$CFLAGS"
export CXXFLAGS="$CXXFLAGS"
export FFLAGS="$FFLAGS"
export LDFLAGS+="-Wl,--rpath=%{_libdir} "

%cmake . -DVERSION=%{version} \
        -DCMAKE_BUILD_TYPE=%{?build_type:%build_type}%{!?build_type:RELEASE} \
        -DCMAKE_VERBOSE_MAKEFILE=ON

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
%make_install

%clean
rm -rf %{buildroot}

%files
%{_bindir}/cert-checker
%{_datadir}/license/%{name}
