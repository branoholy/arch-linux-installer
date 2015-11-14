/*
 * Arch Linux Installer
 * Copyright (C) 2015  Branislav Holý <branoholy@gmail.com>
 *
 * This file is part of Arch Linux Installer.
 *
 * Arch Linux Installer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arch Linux Installer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arch Linux Installer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "archlinuxinstaller/modules/devices/sshdecrypt.hpp"

#include "archlinuxinstaller/packageinstaller.hpp"

#include "archlinuxinstaller/configuration/config.hpp"

namespace archlinuxinstaller {
namespace modules {
namespace devices {

bool SshDecrypt::install(const std::string& grubDevice, const std::string& grubDmname) const
{
	std::vector<std::string> sshDecryptPackages;
	sshDecryptPackages.emplace_back("mkinitcpio-" + network);
	sshDecryptPackages.emplace_back("mkinitcpio-" + sshServer);
	sshDecryptPackages.emplace_back("mkinitcpio-utils");

	PackageInstaller packageInstaller;
	bool status = packageInstaller.installAurPackages(sshDecryptPackages);

	if(packageInstaller.isInstalled("mkinitcpio"))
	{
		configuration::Config mkinitcpio("/etc/mkinitcpio.conf");
		mkinitcpio.setValue("HOOKS", "base udev autodetect modconf block keyboard keymap consolefont " + network + ' ' + sshServer + " encryptssh lvm2 filesystems fsck shutdown");
		mkinitcpio.save();

		status &= utils::SystemUtils::system("mkinitcpio -p linux");
	}

	if(packageInstaller.isInstalled("grub"))
	{
		configuration::Config grubConfig("/etc/default/grub");
		grubConfig.setValue("GRUB_CMDLINE_LINUX", "cryptdevice=" + grubDevice + ':' + grubDmname + " ip=" + ip);
		grubConfig.save();

		status &= utils::SystemUtils::system("grub-mkconfig -o /boot/grub/grub.cfg");
	}

	for(const std::string& key : authorizedKeys)
	{
		status &= utils::SystemUtils::exportKey(key, "/home/" + sshServer + "/root_key");
	}

	return status;
}

}}}

namespace YAML {

bool convert<archlinuxinstaller::modules::devices::SshDecrypt>::decode(const Node& node, archlinuxinstaller::modules::devices::SshDecrypt& sshDecrypt)
{
	if(node.IsMap())
	{
		sshDecrypt.ip = node["ip"].as<std::string>();
		sshDecrypt.network = node["network"].as<std::string>();
		sshDecrypt.sshServer = node["sshServer"].as<std::string>();
		if(node["authorizedKeys"]) sshDecrypt.authorizedKeys = node["authorizedKeys"].as<std::vector<std::string>>();

		return true;
	}

	return false;
}

}