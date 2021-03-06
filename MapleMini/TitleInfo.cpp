#include "stdafx.h"
#include "TitleInfo.h"

static map<int,TitleInfo*> database;
static vector<std::thread> threads;

TitleInfo::TitleInfo()
{
}


TitleInfo::~TitleInfo()
{
}

void TitleInfo::CreateDatabase()
{
	struct json_token t;
	printf("Creating database...\n");
	auto dc = DownloadClient("http://api.tsumes.com/title/all");
	for (int i = 0; json_scanf_array_elem(dc.dataBytes, (int)dc.length, "", i, &t) > 0; i++) {
		thread([](struct json_token t) { 
			auto ti = new TitleInfo;
			json_scanf(t.ptr, t.len, "{uid: %Q}", &ti->uid);
			json_scanf(t.ptr, t.len, "{ID: %Q}", &ti->id);
			json_scanf(t.ptr, t.len, "{Key: %Q}", &ti->key);
			json_scanf(t.ptr, t.len, "{Name: %Q}", &ti->name);
			json_scanf(t.ptr, t.len, "{Region: %Q}", &ti->region);
			json_scanf(t.ptr, t.len, "{Versions: %Q}", &ti->versions);
			json_scanf(t.ptr, t.len, "{HasDLC: %Q}", &ti->hasdlc);
			json_scanf(t.ptr, t.len, "{HasPatch: %Q}", &ti->haspatch);
			json_scanf(t.ptr, t.len, "{ContentType: %Q}", &ti->contenttype);
			json_scanf(t.ptr, t.len, "{AvailableOnCDN: %Q}", &ti->cdn);
			json_scanf(t.ptr, t.len, "{ProductCode: %Q}", &ti->pcode);
			json_scanf(t.ptr, t.len, "{CompanyCode: %Q}", &ti->ccode);
			json_scanf(t.ptr, t.len, "{ImageLocation: %Q}", &ti->iloc);
			json_scanf(t.ptr, t.len, "{Notes: %Q}", &ti->notes);
			database[strtol(ti->id, NULL, 0)] = ti;
			printf("Adding db entry %s\n", ti->name);
		}, t).detach();
	}

	printf("Creating database complete.\n");
	return;
}

TitleInfo::TitleInfo(char * str, size_t len)
{
	struct json_token t;

	for (int i = 0; json_scanf_array_elem(str, (int) len, "", i, &t) > 0; i++) {
		json_scanf(t.ptr, t.len, "{uid: %Q}", &uid);
		json_scanf(t.ptr, t.len, "{ID: %Q}", &id);
		json_scanf(t.ptr, t.len, "{Key: %Q}", &key);
		json_scanf(t.ptr, t.len, "{Name: %Q}", &name);
		json_scanf(t.ptr, t.len, "{Region: %Q}", &region);
		json_scanf(t.ptr, t.len, "{Versions: %Q}", &versions);
		json_scanf(t.ptr, t.len, "{HasDLC: %Q}", &hasdlc);
		json_scanf(t.ptr, t.len, "{HasPatch: %Q}", &haspatch);
		json_scanf(t.ptr, t.len, "{ContentType: %Q}", &contenttype);
		json_scanf(t.ptr, t.len, "{AvailableOnCDN: %Q}", &cdn);
		json_scanf(t.ptr, t.len, "{ProductCode: %Q}", &pcode);
		json_scanf(t.ptr, t.len, "{CompanyCode: %Q}", &ccode);
		json_scanf(t.ptr, t.len, "{ImageLocation: %Q}", &iloc);
		json_scanf(t.ptr, t.len, "{Notes: %Q}", &notes);
		database[strtol(id, NULL, 0)] = this;
	}

	return;
}

#pragma comment(lib,"Urlmon.lib")
int TitleInfo::DownloadContent(const char * outputDir)
{
	auto nusURL = string("http://api.tsumes.com/title/");
	string dir = (string(outputDir) + string("/[") + string(region) + string("] ") + string(name));

	auto _dir = std::wstring(Toolbelt::s2ws(dir));
	if (CreateDirectory(_dir.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{

	}

	string _id(id);
	std::transform(_id.begin(), _id.end(), _id.begin(), ::tolower);

	string tmdPath = dir + string("/tmd");
	string tmdURL = (nusURL + _id + string("/tmd"));

	auto dc = DownloadClient(tmdURL.c_str());
	if (dc.error) return -1;
	Toolbelt::SaveFile(dir.c_str(), dc.dataBytes, (u32)dc.length);
	
	u32 TMDLen;
	char* TMD = Toolbelt::ReadFile(dir.c_str(), &TMDLen);

	if (TMD == nullptr)
	{
		perror("Failed to open tmd\n");
		return -1;
	}

	auto tmd = reinterpret_cast<Decrypt::TitleMetaData*>(TMD);

	for (int i = 0; i < tmd->ContentCount; i++)
	{

	}

	return 0;
}