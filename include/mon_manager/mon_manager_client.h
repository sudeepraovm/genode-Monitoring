#pragma once

#include <base/printf.h>
#include <base/rpc_client.h>
#include <mon_manager/mon_manager_session.h>

namespace Mon_manager {
struct Session_client : Genode::Rpc_client<Session>
{
	Session_client(Genode::Capability<Session> cap):
		Genode::Rpc_client<Session>(cap) {}

	void update_info(Genode::Dataspace_capability ds_cap)
	{
		call<Rpc_update_info>(ds_cap);
	}

	Genode::Dataspace_capability init_ds_cap(int num_threads)
	{
		return call<Rpc_init_ds_cap>(num_threads);
	}

};
}
