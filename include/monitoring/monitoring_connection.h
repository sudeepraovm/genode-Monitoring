#pragma once

#include <monitoring/monitoring_client.h>
#include <base/connection.h>

struct Monitoring_connection : Genode::Connection<Monitoring_session>, Monitoring_session_client
{
	Monitoring_connection() :
		Genode::Connection<Monitoring_session>(session("bar, ram_quota=1M")),

		Monitoring_session_client(cap())
	{
	}
};
