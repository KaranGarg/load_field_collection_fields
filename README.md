# load_field_collection_fields

Load Field Collection Module
====================================================================
Load Field Collection fields module allows to load and attach the field collection entity fields when a node, taxonomy and user entity is loaded. By default, on loading an entity, the only data loaded for a collection field is 'value' and 'revision_id'. And entity_load function has to be called with that field collection field data separately with a lot of loops.

But this module makes the process easy and automatically loads the field collection entity and add the complete entity to the key 'field_items' of the field collection field as soon the entity is being loaded using "node_load", "taxonomy_term_load" or "user_load".


Configuration
====================================================================
Choose the entities for which you want to load field collection fields. Simply navigate to
Configuration >> Fields >> Field collection load fields


