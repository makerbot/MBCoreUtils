Name:		MBCoreUtils
Version:	$MBCoreUtils
Release:	1%{?dist}
Summary:	MakerBot core utility headers

License:	Proprietary
URL:		http://www.makerbot.com/makerware
Source:	        MBCoreUtils-%{version}.tar.gz

BuildRequires:	gcc, jsoncpp-devel >= 0.6.0
Requires:	jsoncpp >= 0.6.0


%description
MakerBot core utility headers

%prep
%setup -q -n %{name}


%build
scons --install-prefix=%{buildroot}/%{_prefix}


%install
rm -rf %{build_root}
scons --install-prefix=%{buildroot}/%{_prefix} install

%files
%{_includedir}/


%changelog

