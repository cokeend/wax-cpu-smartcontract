#include <eosio/eosio.hpp>
#include <eosio/symbol.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>
#include <eosio/print.hpp>
#include <eosio/privileged.hpp>
#include <eosio/singleton.hpp>
#include <eosio/transaction.hpp>


#include <string>
//#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 



using namespace eosio;

using std::endl; using std::string;
using std::vector; using std::istringstream;
    // the data structure which defines each row of the table




class [[eosio::contract("wax")]] wax : public contract {
   

   private:
      const symbol wax_symbol;
     // const asset stake_net_qty;

   public:
      using contract::contract;
       wax( name receiver, name code, datastream<const char*> ds )
         : contract(receiver, code, ds), stakingtab(receiver,receiver.value),configtab(receiver,receiver.value),crontab(receiver,receiver.value), wax_symbol("WAX",8) {}

  /*    [[eosio::contract("eosio.system::delegatebw")]]
      void delegatebw(const name& self,const name& hodler,const asset& quantity2 ,const asset& quantity,bool transfer){
      }; */
 
    [[eosio::on_notify("eosio.token::transfer")]]
      void deposit(name user, name to, eosio::asset quantity, std::string memo)
     // void deposit(const name& self,const name& hodler,const asset& quantity2 ,const asset& quantity,bool transfer)
         {
            
        if (to != get_self() || user == get_self())
         {
            print_f("These are not the droids you are looking for.");
            return;
         }

      //   eosio::asset to_string(quantity) const newqty;


         //check(quantity.amount == 2.5, quantity.amount);
         check(quantity.symbol == wax_symbol, "These are not the droids you are looking for.");
       
  /*    if(memo == "1"){
         
         
      }else{

      }*/
     // stake_net_qty = "100.00000000 WAX";
     name wallet = name("maloanwallet");

      

  // auto itr_pack7d = packagetab.find(0);
   //auto itr_pack15d = packagetab.find(1);
   //auto itr_pack30d = packagetab.find(2);
   
  // check(package1.value != 0 , package1.value);

   auto stake_net_qty = asset(0,wax_symbol);
   auto stake_cpu_qty = asset(10000000000,wax_symbol);
  // auto stake_cpu_qty2 = asset(0,wax_symbol);
   auto price_7d = asset(600000000,wax_symbol);
   auto price_15d = asset(1000000000,wax_symbol);
   auto price_30d = asset(1700000000,wax_symbol);
   auto itr_config = configtab.find(0);
   auto default_quantity = itr_config->default_quantity*100000000;
     // stake_net_qty.set_amount(100);
   //   stake_cpu_qty.set_amount(100);
      //price_7d.set_amount(7);
        if (memo.find(",") != string::npos) {
            //cout << "true";
        
               vector<string> new_memo;
               split(memo, ',', new_memo);
               int custom_day;
               //custom_day = std::stoi(new_memo[1]);
               custom_day = std::atoi(new_memo[1].c_str());
            //   int custom_qty = std::stoi(new_memo[2]);
            int custom_qty = std::atoi(new_memo[2].c_str());
               name stake_to = name(new_memo[3]);
               //custom_day = 0;
             // int  custom_qty = 0;
               //new_memo[0] = "custom";
            //   require_auth(to);
               //
                //eosio::print( "hello world, this is a number: ", new_memo[1] );
               
               //check(memo == "custom,10" , new_memo[1]);
           
         //  check(quantity.amount == 8, new_memo[0]);
           //    check(new_memo[0] == "custom" , "is custom");
            if(new_memo[0] == "stake"){
               if(custom_day >= 7 && custom_day <= 14){
                 // auto price_per_day = price_7d.amount/100000000 / 7;
                 // auto custom_price = price_per_day*custom_day;
                //  custom_price = roundf(custom_price * 100) / 100;
                  //check(new_memo[0] == "custom",custom_price);
                  
                  
                     if(quantity.amount/100000000 >= price_7d.amount/100000000 * custom_qty){
                       // auto multiply = quantity.amount / 100000000 / custom_price;
                      //  auto stake_cpu_qty = asset(default_quantity*multiply,wax_symbol);
                        auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);
                      //  if(itr_config->status == "active"){
                           action{
                              permission_level{get_self(), "active"_n},
                                 "eosio"_n,
                                 "delegatebw"_n,
                                 std::make_tuple(get_self(), stake_to, stake_net_qty , stake_cpu_qty ,false)}
                                 .send();

                                 
                           auto expire = current_time_point() += eosio::days(custom_day);

                           stakelog(user,stake_to,stake_cpu_qty,expire);

                           action{
                              permission_level{get_self(), "active"_n},
                              "eosio.token"_n,
                              "transfer"_n,
                              std::make_tuple(get_self(), wallet, quantity, std::string())
                           }.send();
                       /* }else{
                           stakewallet2(user,stake_cpu_qty,stake_cpu_qty.amount/100000000,custom_day);
                        }*/

                     } 


                   
               }else if(custom_day >= 15 && custom_day <= 29){

                  
                  if((custom_day < 20) && (quantity.amount/100000000 >= price_15d.amount/100000000 * custom_qty)){
                   //  auto multiply = quantity.amount / 100000000 / custom_price;
                     auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);

                     //check(quantity.amount == 9, custom_price);
                    //  if(itr_config->status == "active"){
                        action{
                           permission_level{get_self(), "active"_n},
                              "eosio"_n,
                              "delegatebw"_n,
                              std::make_tuple(get_self(), stake_to, stake_net_qty , stake_cpu_qty ,false)}
                              .send();

                              
                        auto expire = current_time_point() += eosio::days(custom_day);

                        stakelog(user,stake_to,stake_cpu_qty,expire);

                        action{
                           permission_level{get_self(), "active"_n},
                           "eosio.token"_n,
                           "transfer"_n,
                           std::make_tuple(get_self(), wallet, quantity, std::string())
                        }.send();
                  /*   }else{
                        stakewallet2(user,stake_cpu_qty,stake_cpu_qty.amount/100000000,custom_day);
                     }*/
                  }else if((custom_day >= 20) && (quantity.amount/100000000 >= price_15d.amount/100000000 * custom_qty)){
                     auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);

                     //check(quantity.amount == 9, custom_price);
                   //  if(itr_config->status == "active"){
                        action{
                           permission_level{get_self(), "active"_n},
                              "eosio"_n,
                              "delegatebw"_n,
                              std::make_tuple(get_self(), stake_to, stake_net_qty , stake_cpu_qty ,false)}
                              .send();

                              
                        auto expire = current_time_point() += eosio::days(custom_day);

                        stakelog(user,stake_to,stake_cpu_qty,expire);

                        action{
                           permission_level{get_self(), "active"_n},
                           "eosio.token"_n,
                           "transfer"_n,
                           std::make_tuple(get_self(), wallet, quantity, std::string())
                        }.send();
                     /*}else{
                        stakewallet2(user,stake_cpu_qty,stake_cpu_qty.amount/100000000,custom_day);
                     }*/
                  }

                     

               }else if(custom_day >= 30 && custom_day <= 60){
                  if((custom_day < 45) && (quantity.amount/100000000 >= price_30d.amount/100000000 * custom_qty)){
                   //  auto multiply = quantity.amount / 100000000 / custom_price;
                     auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);

                     //check(quantity.amount == 9, custom_price);
                     //if(itr_config->status == "active"){
                        action{
                           permission_level{get_self(), "active"_n},
                              "eosio"_n,
                              "delegatebw"_n,
                              std::make_tuple(get_self(), stake_to, stake_net_qty , stake_cpu_qty ,false)}
                              .send();

                              
                        auto expire = current_time_point() += eosio::days(custom_day);

                        stakelog(user,stake_to,stake_cpu_qty,expire);

                        action{
                           permission_level{get_self(), "active"_n},
                           "eosio.token"_n,
                           "transfer"_n,
                           std::make_tuple(get_self(), wallet, quantity, std::string())
                        }.send();
                   /*  }else{
                        stakewallet2(user,stake_cpu_qty,stake_cpu_qty.amount/100000000,custom_day);
                     }*/
                  }else if((custom_day >= 45) && (quantity.amount/100000000 >= price_30d.amount/100000000 * custom_qty)){
                     auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);

                     //check(quantity.amount == 9, custom_price);
                    // if(itr_config->status == "active"){
                        action{
                           permission_level{get_self(), "active"_n},
                              "eosio"_n,
                              "delegatebw"_n,
                              std::make_tuple(get_self(), stake_to, stake_net_qty , stake_cpu_qty ,false)}
                              .send();

                              
                        auto expire = current_time_point() += eosio::days(custom_day);

                        stakelog(user,stake_to,stake_cpu_qty,expire);

                        action{
                           permission_level{get_self(), "active"_n},
                           "eosio.token"_n,
                           "transfer"_n,
                           std::make_tuple(get_self(), wallet, quantity, std::string())
                        }.send();
                   /*  }else{
                        stakewallet2(user,stake_cpu_qty,stake_cpu_qty.amount/100000000,custom_day);
                     }*/
                  }

               }
            }  // check memo custom
        } /// end check memo
            
           
      
   


      } /// end deposit

void split(const string& s, char c,
   vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void stakewallet2(name user,asset quantity,uint64_t sqty,uint64_t days){

   std::string acc = user.to_string();
   std::string qty = std::to_string(sqty);
   std::string day = std::to_string(days);
   std::string memo = "stake,"+acc+","+qty+","+day;
   name wallet2 = name("maloanwaxme2");
   action{
         permission_level{get_self(), "active"_n},
         "eosio.token"_n,
         "transfer"_n,
         std::make_tuple(get_self(), wallet2, quantity, std::string(memo))
      }.send();


}

   /*    [[eosio::on_notify("eosio.system::transfer")]]
         void delegatebw(const name& self,const name& hodler,const asset& quantity2 ,const asset& quantity,bool transfer){
          
       };*/

      struct [[eosio::table]] staking_table {
         uint64_t id;
         name account;
         time_point_sec start;
         time_point_sec expire;
         asset stakedqty;
         uint64_t primary_key()const { return id; }
      };

    /*  struct [[eosio::table]] package_table {
         uint64_t id;
         name package;
         uint64_t days;
         asset price;
         uint64_t primary_key()const { return id; }
      };*/

      struct [[eosio::table]] config_table {
         uint64_t id;
         uint64_t default_quantity;
         time_point_sec active_period;
         time_point_sec active2_period;
         std::string status;
         uint64_t primary_key()const { return id; }
      };
      struct [[eosio::table]] cron_table {
         uint64_t id;
         uint64_t status;
         uint64_t sec;
         uint64_t primary_key()const { return id; }
      };


  
         typedef eosio::multi_index<"stakinglist"_n, staking_table> staking_t;

        // typedef eosio::multi_index<"package"_n, package_table> package_t;

         typedef eosio::multi_index<"config"_n, config_table> config_t;
         typedef eosio::multi_index<"cron"_n, cron_table> cron_t;

         



      staking_t stakingtab;

     // package_t packagetab;

      config_t configtab;

      cron_t crontab;

      

      //[[eosio::action]] 
     // void setcron(uint64_t status,uint64_t sec);
      [[eosio::action]] 
      void modcron(uint64_t status,uint64_t sec);
      [[eosio::action]] 
      void setconfig(uint64_t default_quantity,std::string status);
      [[eosio::action]] 
      void modconfig(uint64_t default_quantity,time_point_sec active_period,time_point_sec active2_period,std::string status);
      [[eosio::action]] 
     /* void setpackage(name pack,uint64_t days,asset price);
      [[eosio::action]] 
      void modpackage(uint64_t id,uint64_t days,asset price);
      [[eosio::action]] 
      
      void delpackage( uint64_t id );
      [[eosio::action]] */
      void stakelog(name user , name stake_to , asset qty,time_point_sec expire);
      [[eosio::action]] 
      void run();
      [[eosio::action]] 
      void unstake(uint64_t status);
      [[eosio::action]] 
      void modstaking(uint64_t id,time_point_sec expire);
    /*  [[eosio::action]] 
      void delconfig();*/
      using set_config_action = action_wrapper<"setconfig"_n, &wax::setconfig>;
     /* using set_package_action = action_wrapper<"setpackage"_n, &wax::setpackage>;
      using mod_package_action = action_wrapper<"modpackage"_n, &wax::modpackage>;
      using del_package_action = action_wrapper<"delpackage"_n, &wax::delpackage>;*/
      using set_stakelog_action = action_wrapper<"stakelog"_n, &wax::stakelog>;
    //  using set_cron_action = action_wrapper<"setcron"_n, &wax::setcron>;
      using mod_cron_action = action_wrapper<"modcron"_n, &wax::modcron>;
      using run_action = action_wrapper<"run"_n, &wax::run>;
      using unstake_action = action_wrapper<"unstake"_n, &wax::unstake>;
      using mod_staking_action = action_wrapper<"modstaking"_n, &wax::modstaking>;
     // using del_config_action = action_wrapper<"delconfig"_n, &wax::delconfig>;


      
};


