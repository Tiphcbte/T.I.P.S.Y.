#include "ros/ros.h"
#include <iostream>
#include <knowrob_tutorial/Coordinates.h>
#include <knowrob_tutorial/OrderDrink.h>
#include <rosprolog/rosprolog_client/PrologClient.h>
#include <string>

using namespace std;

bool orderDrink(knowrob_tutorial::OrderDrink::Request &req,
                knowrob_tutorial::OrderDrink::Response &resp) {
  PrologClient pl = PrologClient("/rosprolog", true);
  string table_number = "1";

  PrologQuery bdgs = pl.query(
      "rdf_has(drinkOntology:'"+req.name_drink+"', drinkOntology:onTable, Table_number)");

  for (PrologQuery::iterator it = bdgs.begin(); it != bdgs.end(); it++) {
    PrologBindings bdg = *it;
    cout << "Found solution: " << (bool)(it == bdgs.end()) << endl;
    cout << "Table_number = " << bdg["Table_number"] << endl;
    table_number = bdg["Table_number"].toString()[55];
  }
    knowrob_tutorial::Coordinates coordinate;

    if (table_number == "1") {
        resp.coordinate.x = -0.68;
        resp.coordinate.y = -2.17;
        resp.coordinate.Y = 3.14;
    }

    if (table_number == "2") {
        resp.coordinate.x = -0.68;
        resp.coordinate.y = -1.03;
        resp.coordinate.Y = 3.14;
    }

    if (table_number == "3") {
        resp.coordinate.x = -0.68;
        resp.coordinate.y = 1.17;
        resp.coordinate.Y = 3.14;
    }

    if (table_number == "4") {
        resp.coordinate.x = -0.68;
        resp.coordinate.y = 2.13;
        resp.coordinate.Y = 3.14;
    }
    return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "drink_to_coordinates");
  ros::NodeHandle n;

  ros::ServiceServer service =
      n.advertiseService("drink_to_coordinates", &orderDrink);

  ros::spin();
  return 0;
}