#pragma once

#include <base/printf.h>
#include <base/rpc_client.h>
#include <mon_manager/mon_manager_session.h>

namespace Mon_manager {
struct Session_client : Genode::Rpc_client<Session>
{
	Session_client(Genode::Capability<Session> cap):
		Genode::Rpc_client<Session>(cap) {}

	size_t update_info(Genode::Dataspace_capability ds_cap)
	{
		return call<Rpc_update_info>(ds_cap);
	}

	void update_rqs(Genode::Dataspace_capability ds_cap)
	{
		call<Rpc_update_rqs>(ds_cap);
	}

	void update_dead(Genode::Dataspace_capability ds_cap)
	{
		call<Rpc_update_dead>(ds_cap);
	}

	int get_num_cores()
	{
		return call<Rpc_get_num_cores>();
	}

	Genode::Trace::Execution_time get_idle_time(int core)
	{
		return call<Rpc_get_idle_time>(core);
	}

	bool is_core_online(int core)
	{
		return call<Rpc_is_core_online>(core);
	}

	int get_util(int core)
	{
		return call<Rpc_get_util>(core);
	}

};
}
