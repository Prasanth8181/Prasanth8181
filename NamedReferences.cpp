#include "TeamCenterITK.h"



int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;
	tag_t dataset = NULLTAG;
	int iNoOfDataset = 0;
	tag_t *tRefObjects = NULLTAG;
	char *referenceName = NULL;
	AE_reference_type_e refType;
	tag_t refObject = NULLTAG;

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		AE_find_dataset2("000101",&dataset);
		AE_ask_dataset_named_refs(dataset, &iNoOfDataset,&tRefObjects);
		for (int i = 0; i < iNoOfDataset; i++)
		{
			AE_find_dataset_named_ref2(dataset,0, &referenceName, &refType,&refObject);
			AOM_refresh(dataset, true);
			AE_remove_dataset_named_ref_by_tag2(dataset, referenceName, tRefObjects[i]);
			AOM_save_with_extensions(dataset);
			AOM_refresh(dataset, false);
			
		}
	}
	error(loginStatus);
	return 0;
}