#pragma once

#include <session/session.h>
#include <base/rpc.h>
#include <ram_session/ram_session.h>
#include <string>

namespace Mon_manager {

	struct Session : Genode::Session
	{

		static const char *service_name() { return "mon_manager"; }

		virtual void update_info(Genode::Dataspace_capability ds_cap) = 0;

		virtual Genode::Dataspace_capability init_ds_cap(int num_threads) = 0;

		GENODE_RPC(Rpc_update_info, void, update_info, Genode::Dataspace_capability);

		GENODE_RPC(Rpc_init_ds_cap, Genode::Dataspace_capability, init_ds_cap, int);

		GENODE_RPC_INTERFACE(Rpc_update_info, Rpc_init_ds_cap);

	};

}
