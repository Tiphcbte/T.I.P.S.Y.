#include "ros/ros.h"
#include <iostream>
#include <knowrob_tutorial/OrderDrink.h>
#include <rosprolog/rosprolog_client/PrologClient.h>
#include <string>

using namespace std;

bool orderDrink(knowrob_tutorial::OrderDrink::Request &req,
              knowrob_tutorial::OrderDrink::Response &resp) {
    PrologClient pl = PrologClient("/rosprolog", true);
    string A = "empty";

    PrologQuery bdgs = pl.query("rdf_has(DrinkOntology:req.name_drink, DrinkOntology:onTable, A)");

    for (PrologQuery::iterator it = bdgs.begin(); it != bdgs.end(); it++) {
    PrologBindings bdg = *it;
    cout << "Found solution: " << (bool)(it == bdgs.end()) << endl;
    cout << "A = " << bdg["A"] << endl;
    A = bdg["A"].toString()[51];
    }

  resp.table_drink = A;
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "order_drink");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("order_drink", &orderDrink);

  ros::spin();
  return 0;
}