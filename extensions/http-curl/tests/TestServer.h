/**
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIBMINIFI_TEST_TESTSERVER_H_
#define LIBMINIFI_TEST_TESTSERVER_H_

#include <string>
#include <iostream>
#include "civetweb.h"
#include "CivetServer.h"
#include "civetweb.h"
#include "HTTPUtils.h"


/* Server context handle */
static std::string resp_str;

void init_webserver() {
  mg_init_library(0);
}


CivetServer * start_webserver(std::string &port, std::string &rooturi, CivetHandler *handler, struct mg_callbacks *callbacks, std::string &cert, std::string &ca_cert) {
  const char *options[] = { "document_root", ".", "listening_ports", port.c_str(), "error_log_file",
      "error.log", "ssl_certificate", ca_cert.c_str(), "ssl_protocol_version", "4", "ssl_cipher_list",
      "ALL", "request_timeout_ms", "10000", "enable_auth_domain_check", "no", "ssl_verify_peer", "no", 0 };
// ECDH+AESGCM+AES256:!aNULL:!MD5:!DSS
  std::vector<std::string> cpp_options;
  for (size_t i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
    cpp_options.push_back(options[i]);
  }

  if (!mg_check_feature(2)) {
      fprintf(stderr,
              "Error: Embedded example built with SSL support, "
              "but civetweb library build without.\n");
      return 0;
    }


  //mg_init_library(MG_FEATURES_SSL);

  CivetServer *server = new CivetServer(cpp_options, (CivetCallbacks*)callbacks);

  server->addHandler(rooturi, handler);

  return server;

}

CivetServer * start_webserver(std::string &port, std::string &rooturi, CivetHandler *handler) {
  const char *options[] = { "document_root", ".", "listening_ports", port.c_str(), 0 };

  std::vector<std::string> cpp_options;
  for (size_t i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
    cpp_options.push_back(options[i]);
  }
  CivetServer *server = new CivetServer(cpp_options);

  server->addHandler(rooturi, handler);

  return server;

}

static void stop_webserver(CivetServer *server) {
  if (server != nullptr)
    delete server;

  /* Un-initialize the library */
  mg_exit_library();
}

#endif
