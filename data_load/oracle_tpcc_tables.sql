drop table warehouse cascade constraints;
drop table district cascade constraints;
drop table history cascade constraints;
drop table customer  cascade constraints;
drop table cust_order  cascade constraints;
drop table new_order  cascade constraints;
drop table stock cascade constraints;
drop table item cascade constraints;
drop table order_line  cascade constraints;

set echo on
create table warehouse (
W_ID number not null
,W_name varchar2(10)
,W_STREET_1 varchar2(20)
,W_STREET_2 varchar2(20) 
,W_CITY varchar2(20)
,w_state varchar2(2)
,W_ZIP varchar2(9)
,W_TAX number(4,4)
,W_YTD number(12,2)
);

create unique index pk_warehouse on warehouse (w_id);
alter table warehouse add constraint pk_warehouse primary key (w_id) using index pk_warehouse;

-- specifying "using index" allows one to disable the primary key constraint, but keep the index.
-- For example: alter table warehouse drop constraint pk_warehouse KEEP INDEX;
-- This allows for improved bulk data loading speeds, since a constraint is no longer referenced
-- for each row loaded, but the integrity of the table is still intact, since the index is
-- a unique index, so recreating the constraint after a  bulk load, with an absent primary key
-- constraint would be speedier.

create table district (
D_ID number not null
,d_w_id number not null
,d_name varchar2(10)
,d_street_1 varchar2(20)
,d_street_2 varchar2(20)
,d_city varchar2(20)
,d_state varchar2(20)
,d_zip varchar2(9)
,d_tax number(4,4)
,d_ytd number(12,2)
,d_next_o_id number
);

create unique index pk_district on district (d_w_id, D_ID);
alter table district add constraint pk_district primary key (D_W_ID, d_id) using index pk_district;

alter table district add constraint fk_district_warehouse foreign key (d_w_id) references warehouse (w_id);

create table customer (
c_id number  not null
,c_d_id number  not null
,c_w_id number  not null
,c_first varchar2(16)
,c_middle varchar2(2)
,c_last varchar2(16)
,c_street_1 varchar2(20)
,c_street_2 varchar2(20)
,c_city varchar2(20)
,c_state varchar2(2)
,c_zip varchar2(9)
,c_phone varchar2(16)
,c_since date
,c_credit number(12,2)
,c_credit_lim number(12,2)
,c_discount number(4,4)
,c_balance number(12,2)
,c_ytd_payment number(12,2)
,c_payment_cnt number(4)
,c_delivery_cnt number(4)
,c_data varchar2(500)
);

create unique index pk_customer on customer (c_w_id, c_d_id, c_id);
alter table customer add constraint pk_customer primary key (c_w_id, c_d_id, c_id) using index pk_customer;

alter table customer add constraint fk_cust_district foreign key (c_w_id, c_d_id)
references district (d_w_id, d_id);

create table history (
h_c_id number
,h_c_d_id number
,h_c_w_id number
,h_d_id number
,h_w_id number
,h_date date
,h_amount number(6, 2)
,h_data varchar2(24)
);

create index idx_hist_cust on history (H_C_W_ID, H_C_D_ID, H_C_ID);
alter table history add constraint fk_hist_cust foreign key (h_C_W_ID, h_C_D_ID, h_C_ID)
references customer (C_W_ID, C_D_ID, C_ID);

create index idx_hist_district on history (H_W_ID, H_D_ID);
alter table history add constraint fk_hist_district foreign key (H_W_ID, H_D_ID)
references district (d_w_id, d_id);

create table cust_order (
o_id number
,o_d_id number
,o_w_id number
,o_c_id number
,o_entry_d date
,o_carrier_id number
,o_ol_cnt number(2)
,o_all_local number(1)
);

create unique index pk_order on cust_order (o_w_id, o_d_id, o_id);
alter table cust_order add constraint pk_order primary key (o_w_id, o_d_id, o_id) using index pk_order;

create index idx_cust_order_customer on cust_order (o_w_id, o_d_id, o_c_id);
alter table cust_order add constraint fk_order_cust foreign key (o_w_id, o_d_id, o_c_id)
references customer (c_w_id, c_d_id, c_id);

create table new_order (
no_o_id number not null
,no_d_id number not null
,no_w_id number not null
);

create unique index pk_new_order on new_order (no_w_id, no_d_id, no_o_id);
alter table new_order add constraint pk_new_order
primary key (no_w_id, no_d_id, no_o_id) using index pk_new_order;

/* no need to create an additional index for the foreign key, which is advisable in most foreign key table creation, but in this instance the first 3 columns
of the unique index is what the foreign key reference is based on. So Oracle will therefore
use the unique index in order to improve the performance of the refernce lookup.
It is worth noting that as long as the columns that participate in the referencing form the prefix
of the index, and the ordering is as per the reference, then the index will be usable and will suffice.
The other benefit of having the primary key constraint and the foreign key constraint rely on
the single index is that there is a greater probability that the index will be kept "hot".
In other words, a greater portion of the tree representing the index will be kept in MRU as opposed to the LRU of the buffer area.
Given that the Order (named cust_order) is a master table that many other tables refer to, this would be beneficial to the performance of the schema as a whole. */

alter table new_order add constraint fk_new_order_order
foreign key (no_w_id, no_d_id, no_o_id)
references cust_order (o_w_id, o_d_id, o_id);

create table item (
 i_id numeric not null
,i_im_id number
,i_name varchar2(24)
,i_price number(5,2)
,i_data varchar2(50)
);

create unique index pk_item on item (i_id);
alter table item add constraint pk_item primary key (i_id) using index pk_item;

create unique index uk_item_image on item (i_im_id);

create table stock (
s_i_id number not null
,s_w_id number not null
,s_quantity number(4)
,s_dist_01 varchar2(24)
,s_dist_02 varchar2(24)
,s_dist_03 varchar2(24)
,s_dist_04 varchar2(24)
,s_dist_05 varchar2(24)
,s_dist_06 varchar2(24)
,s_dist_07 varchar2(24)
,s_dist_08 varchar2(24)
,s_dist_09 varchar2(24)
,s_dist_10 varchar2(24)
,s_ytd number(8)
,s_order_cnt number(4)
,s_remote_cnt number(4)
,s_data varchar2(50)
);
  

create unique index pk_stock on stock (s_w_id, s_i_id);
alter table stock add constraint pk_stock primary key (s_w_id, s_i_id) using index pk_stock;

alter table stock add constraint fk_stock_warehouse 
foreign key (s_w_id ) references warehouse (w_id) ;

create index idx_stock_item on stock (s_i_id);
alter table stock add constraint fk_stock_item
foreign key (s_i_id ) references item (i_id);

create table order_line (
ol_o_id numeric not null
,ol_d_id numeric not null
,ol_w_id numeric not null
,ol_number numeric not null
,ol_i_id number
,ol_supply_w_id number
,ol_delivery_d number
,ol_quantity number(2)
,ol_amount number (6,2)
,ol_dist_info varchar2(24)
);

create unique index pk_order_line on order_line (OL_W_ID, OL_D_ID, OL_O_ID, OL_NUMBER);
alter table order_line add constraint pk_order_line primary key (OL_W_ID, OL_D_ID, OL_O_ID, OL_NUMBER)
using index pk_order_line;

alter table order_line add constraint fk_order_line_order foreign key (OL_W_ID, OL_D_ID, OL_O_ID)
references cust_order (O_W_ID, O_D_ID, O_ID);

create index idx_order_line_stock on order_line (ol_supply_w_id, ol_i_id);
alter table order_line add constraint fk_order_line_stock foreign key (ol_supply_w_id, ol_i_id)
references stock (s_W_ID, s_i_ID) ;

set echo off
