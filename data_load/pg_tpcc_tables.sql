drop table warehouse cascade;
drop table district cascade ;
drop table history cascade ;
drop table customer  cascade ;
drop table cust_order  cascade ;
drop table new_order  cascade ;
drop table stock cascade ;
drop table item cascade ;
drop table order_line  cascade;

create table warehouse (
W_ID numeric not null
,W_name varchar(10)
,W_STREET_1 varchar(20)
,W_STREET_2 varchar(20) 
,W_CITY varchar(20)
,w_state varchar(2)
,W_ZIP varchar(9)
,W_TAX numeric(4,4)
,W_YTD numeric(12,2)
);

-- indexes are created automatically in PostgreSQL. Indexes cannot be created separate to constraints as in Oracle.
ALTER TABLE warehouse ADD CONSTRAINT pk_warehouse primary key (w_id);

create table district (
D_ID numeric not null
,d_w_id numeric not null
,d_name varchar(10)
,d_street_1 varchar(20)
,d_street_2 varchar(20)
,d_city varchar(20)
,d_state varchar(20)
,d_zip varchar(9)
,d_tax numeric(4,4)
,d_ytd numeric(12,2)
,d_next_o_id numeric
);

alter table district add constraint pk_district primary key (D_W_ID, d_id) ;

-- the prefix of the index created as part of the primary key would assist in the referral
-- it is therefore not necessary to create an index specifically for the foreign key lookup.
alter table district add constraint fk_district_warehouse foreign key (d_w_id) references warehouse (w_id);

create table customer (
c_id numeric not null
,c_d_id numeric not null
,c_w_id numeric not null
,c_first varchar(16)
,c_middle varchar(2)
,c_last varchar(16)
,c_street_1 varchar(20)
,c_street_2 varchar(20)
,c_city varchar(20)
,c_state varchar(2)
,c_zip varchar(9)
,c_phone varchar(16)
,c_since date
,c_credit numeric(12,2)
,c_credit_lim numeric(12,2)
,c_discount numeric(4,4)
,c_balance numeric(12,2)
,c_ytd_payment numeric(12,2)
,c_payment_cnt numeric(4)
,c_delivery_cnt numeric(4)
,c_data varchar(500)
);

alter table customer add constraint pk_customer primary key (c_w_id, c_d_id, c_id) ;

-- the prefix of the index (first 2 columns) created as part of the primary key would assist in the referral
-- it is therefore not necessary to create an index specifically for the foreign key lookup.

alter table customer add constraint fk_cust_district foreign key (c_w_id, c_d_id)
references district (d_w_id, d_id);

create table history (
h_c_id numeric
,h_c_d_id numeric
,h_c_w_id numeric
,h_d_id numeric
,h_w_id numeric
,h_date date
,h_amount numeric(6, 2)
,h_data varchar(24)
);

create index idx_hist_customer on history (h_C_W_ID, h_C_D_ID, h_C_ID);
alter table history add constraint fk_hist_cust foreign key (h_C_W_ID, h_C_D_ID, h_C_ID)
references customer (C_W_ID, C_D_ID, C_ID);

create index idx_hist_district on history (H_W_ID, H_D_ID);
alter table history add constraint fk_hist_district foreign key (H_W_ID, H_D_ID)
references district (d_w_id, d_id);

create table cust_order (
o_id numeric
,o_d_id numeric
,o_w_id numeric
,o_c_id numeric
,o_entry_d date
,o_carrier_id numeric
,o_ol_cnt numeric(2)
,o_all_local numeric(1)
);

alter table cust_order add constraint pk_order primary key (o_w_id, o_d_id, o_id) ;

create index idx_cust_order_customer on cust_order (o_w_id, o_d_id, o_c_id);
alter table cust_order add constraint fk_order_cust foreign key (o_w_id, o_d_id, o_c_id)
references customer (c_w_id, c_d_id, c_id);

create table new_order (
no_o_id numeric  not null
,no_d_id numeric not null
,no_w_id numeric not null
);

alter table new_order add constraint pk_new_order 
primary key (no_w_id, no_d_id, no_o_id) ;

alter table new_order add constraint fk_new_order_order 
foreign key (no_w_id, no_d_id, no_o_id)
references cust_order (o_w_id, o_d_id, o_id);

create table item (
  i_id numeric not null
,i_im_id numeric
,i_name varchar(24)
,i_price numeric(5,2)
,i_data varchar(50)
);

alter table item add constraint pk_item primary key (i_id);

create unique index uk_item_image on item (i_im_id);

create table stock (
s_i_id numeric not null
,s_w_id numeric not null
,s_quantity numeric(4)
,s_dist_01 varchar(24)
,s_dist_02 varchar(24)
,s_dist_03 varchar(24)
,s_dist_04 varchar(24)
,s_dist_05 varchar(24)
,s_dist_06 varchar(24)
,s_dist_07 varchar(24)
,s_dist_08 varchar(24)
,s_dist_09 varchar(24)
,s_dist_10 varchar(24)
,s_ytd numeric(8)
,s_order_cnt numeric(4)
,s_remote_cnt numeric(4)
,s_data varchar(50)
);

alter table stock add constraint pk_stock primary key (s_w_id, s_i_id);

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
,ol_i_id numeric
,ol_supply_w_id numeric
,ol_delivery_d numeric
,ol_quantity numeric(2)
,ol_amount numeric (6,2)
,ol_dist_info varchar(24)
);

alter table order_line
add constraint pk_order_line primary key (OL_W_ID, OL_D_ID, OL_O_ID, ol_number);

alter table order_line add constraint fk_order_line_order foreign key (OL_W_ID, OL_D_ID, OL_O_ID)
references cust_order (O_W_ID, O_D_ID, O_ID);

create index idx_order_line_stock on order_line (ol_supply_w_id, ol_i_id);
alter table order_line add constraint fk_order_line_stock foreign key (ol_supply_w_id, ol_i_id)
references stock (s_W_ID, s_i_ID);
