/opt/sqlanywhere17/bin64s/dbisql -c "uid=sadb;pwd=sadb;eng=ftnode_sa;links=tcpip(host=10.11.12.17;port=49153);LOG=conn.log;dbn=ftnode_sa" sa_tpcc_tables.sql
/opt/sqlanywhere17/bin64s/dbisql -c "uid=sadb;pwd=sadb;eng=ftnode_sa;links=tcpip(host=10.11.12.17;port=49153);LOG=conn.log;dbn=ftnode_sa" sa_warehouse_district_data.sql
/opt/sqlanywhere17/bin64s/dbisql -c "uid=sadb;pwd=sadb;eng=ftnode_sa;links=tcpip(host=10.11.12.17;port=49153);LOG=conn.log;dbn=ftnode_sa" sa_customer_inserts.sql
/opt/sqlanywhere17/bin64s/dbisql -c "uid=sadb;pwd=sadb;eng=ftnode_sa;links=tcpip(host=10.11.12.17;port=49153);LOG=conn.log;dbn=ftnode_sa" sa_item_inserts_50k.sql 
