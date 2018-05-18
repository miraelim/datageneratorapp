#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv)
{
    json_object *myobj, *headerobj, *dataobj, *schemaobj, *effectimeobj, *bodyobj, *systolicobj, *diastolicobj;

    myobj = json_object_new_object();

    headerobj = json_object_new_object();
    dataobj   = json_object_new_object();
    schemaobj   = json_object_new_object();
    effectimeobj   = json_object_new_object();
    bodyobj   = json_object_new_object();
    systolicobj   = json_object_new_object();
    diastolicobj   = json_object_new_object();

    /* header { ..., } 영역 */
    json_object_object_add(headerobj, "id", json_object_new_string("ec4bf973-ea36-49f3-9aaa-69c18c9c7d03"));
    json_object_object_add(headerobj, "creation_date_time", json_object_new_string("2015-01-01T01:48:19Z"));
    json_object_object_add(myobj, "header", headerobj);

    /* data { ..., nameInfo { ..., } phoneNumber [ ..., ] } 영역 */
    json_object_object_add(dataobj, "source_name", json_object_new_string("generator"));
    json_object_object_add(dataobj, "source_creation_date_time", json_object_new_string("2015-01-01T01:47:19Z"));

    json_object_object_add(headerobj, "acquisition_provenance", dataobj);
    json_object_object_add(headerobj, "user_id", json_object_new_string("some-user"));

    json_object_object_add(schemaobj, "namespace", json_object_new_string("omh"));
    json_object_object_add(schemaobj, "name", json_object_new_string("blood-pressure"));
    json_object_object_add(schemaobj, "version", json_object_new_string("1.0"));

    json_object_object_add(headerobj, "schema_id", schemaobj);

    json_object_object_add(effectimeobj, "date_time", json_object_new_string("2015-01-01T01:47:19Z"));

    json_object_object_add(bodyobj, "effective_time_frame", effectimeobj);

    json_object_object_add(systolicobj, "unit", json_object_new_string("mmHg"));
    json_object_object_add(systolicobj, "value", json_object_new_double(123.27212147153132));

    json_object_object_add(bodyobj, "systolic_blood_pressure", systolicobj);


    json_object_object_add(diastolicobj, "unit", json_object_new_string("mmHg"));
    json_object_object_add(diastolicobj, "value", json_object_new_double(80.96460635879785));

    json_object_object_add(bodyobj, "diastolic_blood_pressure", diastolicobj);



    json_object_object_add(myobj, "body", bodyobj);








    printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));

    json_object_put(headerobj);
    json_object_put(dataobj);
    json_object_put(myobj);
    return(0);
}
