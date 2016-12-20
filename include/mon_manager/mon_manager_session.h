#pragma once

#include <session/session.h>
#include <base/rpc.h>
#include <ram_session/ram_session.h>
#include <string>
#include <trace_session/connection.h>

namespace Mon_manager {

	struct Session : Genode::Session
	{

		static const char *service_name() { return "mon_manager"; }

		virtual void update_info(Genode::Dataspace_capability ds_cap) = 0;

		virtual Genode::Dataspace_capability init_ds_cap(int num_threads) = 0;

		virtual int get_num_cores() = 0;

		virtual Genode::Trace::Execution_time get_idle_time(int core) = 0;

		virtual bool is_core_online(int core) = 0;

		GENODE_RPC(Rpc_update_info, void, update_info, Genode::Dataspace_capability);

		GENODE_RPC(Rpc_init_ds_cap, Genode::Dataspace_capability, init_ds_cap, int);

		GENODE_RPC(Rpc_get_num_cores, int, get_num_cores);

		GENODE_RPC(Rpc_get_idle_time, Genode::Trace::Execution_time, get_idle_time, int);

	 	GENODE_RPC(Rpc_is_core_online, bool, is_core_online, int);

		GENODE_RPC_INTERFACE(Rpc_update_info, Rpc_init_ds_cap, Rpc_get_num_cores, Rpc_get_idle_time, Rpc_is_core_online);

	};

}
