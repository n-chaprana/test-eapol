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
#ifndef __EAP_ON_ETHERNET_H__
#define __EAP_ON_ETHERNET_H__

#include "net_connection.h"
#include "connection_profile.h"
#include "connection_extension.h"

#include "EapOnEthernet.h"
#include "EapUtil.h"

typedef struct {
	connection_ethernet_eap_type_e type;
	connection_ethernet_eap_auth_type_e auth_type;
	const char *identity;
	const char *password;
	const char *anonymous_identity;
	const char *ca_cert_filename;
	const char *client_cert_filename;
	const char *private_key_filename;
	const char *private_key_password;
	const char *pac_filename;
	connection_ethernet_eap_peap_version_e peap_version;
} eap_on_ethernet_s;

class EapOnEthernet {
private:
	connection_h connection;
	bool use_eapol;
	eap_on_ethernet_s eap_settings;

	static connection_error_e connected_result;
	static GMainLoop *mainLoop;
	static guint timeoutId;

	static void connectionOpenedCallback(connection_error_e result, void* user_data);
	static void connectionClosedCallback(connection_error_e result, void* user_data);
	static gboolean timeout_callback(gpointer data);

	static void runGMainLoop(int timeout);
	static void quitGMainLoop(void);

	error_e GetEthernetProfile(connection_profile_h &profile);
	error_e ApplyEapSettings(connection_profile_h profile);
	error_e OpenConnection(connection_profile_h profile);
	error_e CloseConnection(connection_profile_h profile);
public:
	EapOnEthernet(void);
	EapOnEthernet(bool user_eapol, eap_on_ethernet_s eap_settings);
	~EapOnEthernet(void);

	error_e checkEthernetConnection(void);
};

#endif /* __EAP_ON_ETHERNET_H__ */
