#pragma once
#include <string>

class c_recv_table;
class c_recv_prop;

typedef void( *recv_var_proxy_fn )( const void* pData, void* pStruct, void* pOut );
typedef void( *array_length_recv_proxy_fn )( void* pStruct, int objectID, int currentArrayLength );
typedef void( *data_table_recvvar_proxy_fn )( const c_recv_prop* pProp, void** pOut, void* pData, int objectID );

class c_recv_prop {
public:
	char* m_varname;
	int m_recvtype;
	int m_flags;
	int m_stringbuffsize;
	int m_inside_arary;
	const void* m_extractdata;
	c_recv_prop* m_arrayprop;
	array_length_recv_proxy_fn m_arraylengthproxy;
	recv_var_proxy_fn m_proxy;
	data_table_recvvar_proxy_fn m_datatable_proxy;
	c_recv_table* m_datatable;
	int m_offset;
	int m_elementstride;
	int m_elements;
	const char* m_parrent_array_propname;
};

class c_recv_table {
public:
	c_recv_prop* m_props;
	int m_propscount;
	void* m_decoder;
	char* m_net_tablename;
	bool m_initialized;
	bool m_mainlist;
};
