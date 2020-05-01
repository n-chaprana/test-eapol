Name:		connection-test-eapol
Summary:	EAP on Ethernet test utility
Version:	0.0.1
Release:	0
Group:		Network/Testing
License:	Apache-2.0
Source0:	%{name}-%{version}.tar.gz
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-base-common)
BuildRequires:	pkgconfig(capi-network-connection)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(gio-2.0)
BuildRequires:	pkgconfig(gmock)
BuildRequires:	pkgconfig(dlog)

%description
EAP on Ethernet automatic test utility based on gtest.

%prep
%setup -q

%build
cmake .
make %{?_smp_mflags}

%install
%make_install

%post

%postun

%files
%manifest connection-test-eapol.manifest
%license LICENSE
%{_bindir}/connection_test_eapol
