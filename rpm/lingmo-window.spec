%global majver 1
%global libver %{majver}

Name:           lingmo-window
Version:        1.0.0
Release:        1%{?dist}
Summary:        Lingmo Desktop - Application Window Base Library

License:        GPL-2.0-or-later
URL:            https://lingmo.org
Source0:        %{name}-%{version}.tar.xz

BuildRequires:  cmake >= 3.21
BuildRequires:  qt6-qtbase-devel >= 6.5
BuildRequires:  qt6-qtdeclarative-devel >= 6.5
BuildRequires:  lingmo-theme-devel >= 1.0.0

%description
Lingmo Window provides application window abstraction for the Lingmo
Desktop environment, including CSD support, window effects, and
platform window management.

%package -n liblingmowindow%{libver}
Summary:        Runtime libraries for lingmo-window
Requires:       %{name}-libs%{?isa} = %{version}-%{release}

%description -n liblingmowindow%{libver}
Runtime libraries for lingmo-window.

%package -n liblingmowindow-devel
Summary:        Development files for lingmo-window
Requires:       liblingmowindow%{libver}%{?isa} = %{version}-%{release}
Requires:       lingmo-theme-devel

%description -n liblingmowindow-devel
Headers and CMake integration for building applications that use lingmo-window.

%package -n qml6-lingmowindow
Summary:        QML bindings for lingmo-window
Requires:       liblingmowindow%{libver}%{?isa} = %{version}-%{release}
Requires:       qml6-lingmo-theme

%description -n qml6-lingmowindow
QML module providing Window, HeaderBar, Dialog, and WindowEffects types.

%prep
%autosetup

%build
%cmake -DBUILD_TESTING=OFF -DBUILD_EXAMPLES=OFF
%cmake_build

%install
%cmake_install

%check
%ctest

%files -n liblingmowindow%{libver}
%{_libdir}/libLingmoWindow.so.*
%license LICENSE
%doc README.md

%files -n liblingmowindow-devel
%{_includedir}/LingmoWindow/
%{_libdir}/libLingmoWindow.so
%{_libdir}/cmake/LingmoWindow/
%license LICENSE
%doc README.md

%files -n qml6-lingmowindow
%{_libdir}/qt6/qml/Lingmo/Window/
%license LICENSE

%changelog
* Mon Jan 01 2026 Lingmo OS Team <team@lingmo.org> - 1.0.0-1
- Initial release.
