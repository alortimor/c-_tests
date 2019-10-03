psql -h 10.11.12.11 ft_node -U pg -p 5432 -f /home/mw/data_loading/pg_tpcc_tables.sql 
psql -h 10.11.12.11 ft_node -U pg -p 5432 -f /home/mw/data_loading/pg_warehouse_district_data.sql
psql -h 10.11.12.11 ft_node -U pg -p 5432 -f /home/mw/data_loading/pg_customer_inserts.sql
psql -h 10.11.12.11 ft_node -U pg -p 5432 -f /home/mw/data_loading/pg_item_inserts_50k.sql

