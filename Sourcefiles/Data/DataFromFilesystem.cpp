#include "../../Headerfiles/Data/DataFromFilesystem.hpp"
#include "../../Headerfiles/Common/Paths.hpp"

#include <filesystem>

void bx::DataFromFilesystem::assetsDatabaseData(DatabaseManager& assetsDatabase, DataToCreateAssetsDatabase& data) {
	std::filesystem::path texturesParentPath(Paths::assets + "/Textures");
	std::string currentTableName, textureType;
	int index = -1;

	for (auto& entry : std::filesystem::recursive_directory_iterator(Paths::assets)) {
		if (entry.is_directory() && entry.path().parent_path().string() == Paths::assets) {

			data.tableNames.push_back(entry.path().stem().string());
			currentTableName = entry.path().stem().string();

			if (currentTableName == "Textures") { 
				data.columnNamesOfTables.push_back(std::vector<std::string>{ "Name", "Path", "Texture Type" }); 
				data.isColumnUnique.push_back(std::vector<bool>{true, true, false});
			}
			else { 
				data.columnNamesOfTables.push_back(std::vector<std::string>{ "Name", "Path" }); 
				data.isColumnUnique.push_back(std::vector<bool>{true, true});
			}

			data.entries.resize(++index + 1);
		}
		else if (entry.is_directory() && entry.path().parent_path() == texturesParentPath) {
			textureType = entry.path().stem().string();
		}
		else if (entry.is_regular_file()) {
			if (currentTableName == "Textures") {
				data.entries[index].push_back(std::vector<std::string>{ entry.path().stem().string(), entry.path().string(), textureType });
			}
			else {
				data.entries[index].push_back(std::vector<std::string>{ entry.path().stem().string(), entry.path().string() });
			}
		}
	}
}
