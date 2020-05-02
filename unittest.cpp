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
#include <unistd.h>
#include <sys/socket.h>
#include <glib.h>

#include "EapOnEthernet.h"

using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using namespace std;

/*
 * Testcase: MD5 ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionMD5_p)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_MD5,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_NONE,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = NULL,
		.ca_cert_filename = NULL,
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: TLS ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionTLS_p)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_TLS,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_NONE,
		.identity = "private_key_filename",
		.password = NULL,
		.anonymous_identity = NULL,
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = "/certs/client.pem",
		.private_key_filename = "/certs/client.key",
		.private_key_password = "password",
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (TTLS + PAP) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionTTLS_p1)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_TTLS,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_PAP,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (TTLS + MSCHAP) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionTTLS_p2)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_TTLS,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MSCHAP,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (TTLS + MSCHAPV2) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionTTLS_p3)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_TTLS,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MSCHAPV2,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MSCHAPV2 + PEAP_AUTO) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p1)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MSCHAPV2,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + GTC + PEAP_AUTO) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p2)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_GTC,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MD5 + PEAP_AUTO) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p3)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MD5,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_AUTO
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MSCHAPV2 + PEAP_V0) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p4)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MSCHAPV2,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_0
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + GTC + PEAP_V0) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p5)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_GTC,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_0
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MD5 + PEAP_V0) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionPEAP_p6)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MD5,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_0
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MSCHAPV2 + PEAP_V1) ethernet connection.
 * This depends on Radius server, if it supports peapver=1 then
 * connection should succeed.
 */
TEST(EapOnEthernet, DISABLED_checkEthernetConnectionPEAP_p7)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MSCHAPV2,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_1
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + GTC + PEAP_V1) ethernet connection.
 * This depends on Radius server, if it supports peapver=1 then
 * connection should succeed.
 */
TEST(EapOnEthernet, DISABLED_checkEthernetConnectionPEAP_p8)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_GTC,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_1
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: (PEAP + MD5 + PEAP_V1) ethernet connection.
 * This depends on Radius server, if it supports peapver=1 then
 * connection should succeed.
 */
TEST(EapOnEthernet, DISABLED_checkEthernetConnectionPEAP_p9)
{
	error_e ret = ERROR_NONE;
	eap_on_ethernet_s settings = {
		.type = CONNECTION_ETHERNET_EAP_TYPE_PEAP,
		.auth_type = CONNECTION_ETHERNET_EAP_AUTH_TYPE_MD5,
		.identity = "testing",
		.password = "password",
		.anonymous_identity = "anonymous",
		.ca_cert_filename = "/certs/ca.crt",
		.client_cert_filename = NULL,
		.private_key_filename = NULL,
		.private_key_password = NULL,
		.pac_filename = NULL,
		.peap_version = CONNECTION_ETHERNET_EAP_PEAP_VERSION_1
	};

	EapOnEthernet eapol(true, settings);

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

/*
 * Testcase: Normal ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionNormal_p)
{
	error_e ret = ERROR_NONE;
	EapOnEthernet eapol;

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

int main(int argc, char **argv)
{
	int ret = -1;

	if (system("date -s '02 May 2020 18:00:00'") == -1)
		std::cout << "Exception occurred. (System time not updated)" << std::endl;

	try {
		testing::InitGoogleTest(&argc, argv);
	} catch(...) {
		std::cout << "Exception occurred." << std::endl;
	}

	try {
		ret = RUN_ALL_TESTS();
	} catch (const ::testing::internal::GoogleTestFailureException& e) {
		ret = -1;
		std::cout << "GoogleTestFailureException was thrown:" << e.what() << std::endl;
	}

	return ret;
}
