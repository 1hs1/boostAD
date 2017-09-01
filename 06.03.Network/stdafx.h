// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "tp/tp_network.h"

void recieve_auth_task(const boost::system::error_code& err, const detail::tcp_connection_ptr& soc, const boost::shared_ptr<std::string>& data);
void finsh_socket_auth_task(
	const boost::system::error_code& err,
	std::size_t bytes_transfered,
	const detail::tcp_connection_ptr& soc,
	const boost::shared_ptr<std::string>& data);
