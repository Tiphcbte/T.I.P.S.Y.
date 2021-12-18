:- register_ros_package(knowrob_maps).
:- register_ros_package(knowrob_actions).
:- register_ros_package(knowrob_common).


:- consult('instance_utils').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parse OWL files, register name spaces
:- owl_parser:owl_parse('package://knowrob_tutorial/owl/ssy235Ontology.owl').
:- rdf_db:rdf_register_ns(ssy235Ontology, 'http://www.chalmers.se/ontologies/ssy235Ontology.owl#', [keep(true)]).

:- owl_parser:owl_parse('package://knowrob_tutorial/owl/drinkOntology.owl').
:- rdf_db:rdf_register_ns(drinkOntology, 'http://www.semanticweb.org/sv/ontologies/2021/10/drinksOntology#', [keep(true)]).