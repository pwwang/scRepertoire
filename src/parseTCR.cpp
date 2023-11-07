// Helpers for .parseTCR in utils.R
// By Qile Yang

#include <Rcpp.h>
#include <string>
#include <vector>
#include <unordered_map>

#define BarcodeIndciesMap std::unordered_map<std::string, std::vector<int>>

BarcodeIndciesMap stringToIndiciesMap(std::vector<std::string>& v) {
    BarcodeIndciesMap map;
    for (int i = 0; i < (int) v.size(); i++) {
        if (map.find(v[i]) == map.end()) {
            map[v[i]] = {};
        }
        map[v[i]].push_back(i + 1); // + 1 for R indexing, otherwise i for C++ indexing
    }
    return map;
}

// [[Rcpp::export]]
std::vector<std::vector<int>> constructBarcodeIndex(
    std::vector<std::string>& conDfBarcodes, std::vector<std::string>& data2Barcodes
) {
    std::vector<std::vector<int>> outputBarcodeIndex (conDfBarcodes.size());
    BarcodeIndciesMap data2BarcodeIndiciesMap = stringToIndiciesMap(data2Barcodes);

    for (int i = 0; i < (int) conDfBarcodes.size(); i++) {
        std::string& barcode = conDfBarcodes[i];
        if (data2BarcodeIndiciesMap.find(barcode) != data2BarcodeIndiciesMap.end()) {
            outputBarcodeIndex[i] = data2BarcodeIndiciesMap[barcode];
        }
    }

    return outputBarcodeIndex;
}

// // [[Rcpp::export]]
// Rcpp::Dataframe rcppParseTcr(Rcpp::Dataframe& conDf, Rcpp::Dataframe& data2) {
//     Rcpp::CharacterVector conDfBarcodes = conDf[0]; // this is a reference and is equivalent to unique_df
//     Rcpp::CharacterVector data2Barcodes = data2[0];

//     if (conDfBarcodes.size() == 0) {
//         return conDf;
//     }

//     std::vector<std::vector<int>> barcodeIndex = constructBarcodeIndex(conDfBarcodes, data2Barcodes)

//     for (int y = 0; y < (int) conDfBarcodes.size(); y++) {
//         std::vector<int> indicies = barcodeIndex[y];
//         if (indicies.size() == 0) {
//             continue;
//         }

//         // for (int x = 0; x < (int) conDf.size(); x++) {
//         //     conDf[x][y] = data2[x][indicies[0]];
//         //     for (int i = 1; i < (int) index.size(); i++) {
//         //         conDf[x][y] += "," + data2[x][index[i]];
//         //     }
//         // }
//     }

//     return conDf;
// }