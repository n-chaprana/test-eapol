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

	connection_create(&connection);
}

EapOnEthernet::EapOnEthernet(bool use_eapol, eap_on_ethernet_s eap_settings)
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

	connection_create(&connection);
}

EapOnEthernet::~EapOnEthernet(void)
{
	connection_destroy(connection);
}

error_e EapOnEthernet::GetEthernetProfile(connection_profile_h &profile)
{
	connection_profile_iterator_h profile_iter;
	connection_profile_h profile_h;
	connection_profile_type_e profile_type;
	int rv = 0;

	rv = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED,
			&profile_iter);
	if (rv != CONNECTION_ERROR_NONE) {
		GLOGD("Fail to get profile iterator");
		return ERROR_OPERATION_FAILED;
	}

	while (connection_profile_iterator_has_next(profile_iter)) {
		if (connection_profile_iterator_next(profile_iter, &profile_h)
				!= CONNECTION_ERROR_NONE) {
			GLOGD("Fail to get profile handle");
			return ERROR_OPERATION_FAILED;
		}

		if (connection_profile_get_type(profile_h, &profile_type)
				!= CONNECTION_ERROR_NONE) {
			GLOGD("Fail to get profile type");
			return ERROR_OPERATION_FAILED;
		}

		if (profile_type == CONNECTION_PROFILE_TYPE_ETHERNET) {
			GLOGD("Found ethernet profile");
			profile = profile_h;
			return ERROR_NONE;
		}
	}

	return ERROR_OPERATION_FAILED;
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

void EapOnEthernet::connectionOpenedCallback(connection_error_e result, void* user_data)
{
	if (result ==  CONNECTION_ERROR_NONE)
		GLOGD("Connection open Succeeded");
	else
		GLOGD("Connection open Failed");
}

error_e EapOnEthernet::OpenConnection(connection_profile_h profile)
{
	if (connection_open_profile(connection, profile,
				EapOnEthernet::connectionOpenedCallback, NULL)
			!= CONNECTION_ERROR_NONE) {
		GLOGD("Connection open Failed!!");
		return ERROR_OPERATION_FAILED;
	}

	return ERROR_NONE;
}

error_e EapOnEthernet::checkEthernetConnection(void)
{
	GLOGD("Executing test case");
	connection_profile_h profile;
	error_e ret = ERROR_NONE;

	GetEthernetProfile(profile);

	if (use_eapol) {
		ret = ApplyEapSettings(profile);
		if (ret != ERROR_NONE)
			return ret;
	}

	OpenConnection(profile);

	GLOGD("Executed test case");
	return ERROR_NONE;
}
