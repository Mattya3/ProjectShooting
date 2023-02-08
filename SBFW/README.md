
利用したいライブラリで以下をcmakeに追加する
target_include_directories(Setting PUBLIC ${PROJECT_SOURCE_DIR}/SBFW)
target_link_libraries(Setting sbfw)

またprojectのcmakeには
add_subdirectoryも行う

https://qiita.com/mitsuruk9999/items/f1c61cf9a35e57056ab2
