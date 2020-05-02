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
 * Testcase: Normal ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionNormal_p)
{
	error_e ret = ERROR_NONE;
	EapOnEthernet eapol;

	ret = eapol.checkEthernetConnection();
	EXPECT_EQ(ERROR_NONE, ret);
}

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
 * Testcase: (TTLS + MSCHAPV2) ethernet connection.
 */
TEST(EapOnEthernet, checkEthernetConnectionTTLS_p1)
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

int main(int argc, char **argv)
{
	int ret = -1;

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
