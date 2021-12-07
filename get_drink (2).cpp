#include "ros/ros.h"
#include <iostream>
#include <knowrob_tutorial/GetDrink.h>
#include <rosprolog/rosprolog_client/PrologClient.h>
#include <string>

using namespace std;

bool getDrink(knowrob_tutorial::GetDrink::Request &req,
              knowrob_tutorial::GetDrink::Response &resp) {
  PrologClient pl = PrologClient("/rosprolog", true);

  string A = "empty";
  string B = "empty";

  if (req.type_drink == "Alcoholic") {
    PrologQuery bdgs = pl.query("owl_individual_of(A,drinksOntology:'Alcoholic_"
                                "drinks'),rdf_has(A, drinksOntology:hasId, B)");

    for (PrologQuery::iterator it = bdgs.begin(); it != bdgs.end(); it++) {
      PrologBindings bdg = *it;
      cout << "Found solution: " << (bool)(it == bdgs.end()) << endl;
      cout << "A = " << bdg["A"] << endl;
      cout << "B = " << bdg["B"] << endl;
      A = bdg["A"].toString();
      A = A.substr(64, 72);
      B = bdg["B"].toString()[51];
    }

  } else if (req.type_drink == "Non-Alcoholic") {
    PrologQuery bdgs =
        pl.query("owl_individual_of(A,drinksOntology:'Non-alcoholic_drinks'),"
                 "rdf_has(A, drinksOntology:hasId, B)");

    for (PrologQuery::iterator it = bdgs.begin(); it != bdgs.end(); it++) {
      PrologBindings bdg = *it;
      cout << "Found solution: " << (bool)(it == bdgs.end()) << endl;
      cout << "A = " << bdg["A"] << endl;
      cout << "B = " << bdg["B"] << endl;
      A = bdg["A"].toString();
      A = A.substr(64, 77);
      B = bdg["B"].toString()[51];
    }
  }

  resp.class_drink = A;
  resp.id_drink = B;

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "get_drink");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("get_drink", &getDrink);

  ros::spin();
  return 0;
}