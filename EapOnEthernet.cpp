/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdint.h>

#include "EapOnEthernet.h"

EapOnEthernet::EapOnEthernet(void)
{
	use_eapol = true;
	eap_settings.type = CONNECTION_ETHERNET_EAP_TYPE_MD5;
	eap_settings.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_NONE;
	eap_settings.identity = "testing";
	eap_settings.password = "password";
	eap_settings.anonymous_identity = NULL;
	eap_settings.ca_cert_filename = NULL;
	eap_settings.client_cert_filename = NULL;
	eap_settings.private_key_filename = NULL;
	eap_settings.private_key_password = NULL;
	eap_settings.pac_filename = NULL;
	eap_settings.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO;
}

EapOnEthernet::EapOnEthernet(bool user_eapol, eap_on_ethernet_s eap_settings)
{
	this->use_eapol = use_eapol;
	this->eap_settings.type = eap_settings.type;
	this->eap_settings.auth_type = eap_settings.auth_type;
	this->eap_settings.identity = eap_settings.identity;
	this->eap_settings.password = eap_settings.password;
	this->eap_settings.anonymous_identity = eap_settings.anonymous_identity;
	this->eap_settings.ca_cert_filename = eap_settings.ca_cert_filename;
	this->eap_settings.client_cert_filename = eap_settings.client_cert_filename;
	this->eap_settings.private_key_filename = eap_settings.private_key_filename;
	this->eap_settings.private_key_password = eap_settings.private_key_password;
	this->eap_settings.pac_filename = eap_settings.pac_filename;
	this->eap_settings.peap_version = eap_settings.peap_version;
}

EapOnEthernet::~EapOnEthernet(void)
{
}

error_e EapOnEthernet::ApplyEapSettings(connection_profile_h profile)
{
	connection_profile_enable_ethernet_eap(profile, use_eapol);
	switch (eap_settings.type) {
		case CONNECTION_ETHERNET_EAP_TYPE_MD5:
			connection_profile_set_ethernet_eap_passphrase(profile,
				       	eap_settings.identity, eap_settings.password);
			break;
		default:
			GLOGD("Unhandled eap method");
			return ERROR_OPERATION_FAILED;
	}

	return ERROR_NONE;
}

error_e EapOnEthernet::checkEthernetConnection(void)
{
	GLOGD("Executing test case");
	connection_profile_h profile;
	error_e ret = ERROR_NONE;

	if (use_eapol) {
		ret = ApplyEapSettings(profile);
		if (ret != ERROR_NONE)
			return ret;
	}

	return ERROR_NONE;
}
