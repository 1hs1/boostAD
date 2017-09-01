// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "tp/tp_network.h"

void recieve_auth_task(const boost::system::error_code& err, const detail::tcp_connection_ptr& soc, const boost::shared_ptr<std::string>& data);
void finsh_socket_auth_task(
	const boost::system::error_code& err,
	std::size_t bytes_transfered,
	const detail::tcp_connection_ptr& soc,
	const boost::shared_ptr<std::string>& data);
