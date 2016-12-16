#pragma once

#include <mon_manager/mon_manager_client.h>
#include <base/connection.h>

namespace Mon_manager {

	struct Connection : Genode::Connection<Session>, Session_client
	{
		Connection() : Genode::Connection<Mon_manager::Session>(session("mon_manager, ram_quota=4096")),
		               Session_client(cap()) { }
	};


}
