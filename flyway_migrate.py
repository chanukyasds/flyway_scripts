import os
import requests
import ast  # for safely evaluating strings containing Python values from untrusted sources 
from datetime import datetime


print("\nGathering Flyway deployment information...")
# get the deployment configuration from git
headers = {
    "Cache-Control": "no-cache",
    "Pragma": "no-cache"
}
git_config_file_url='https://raw.githubusercontent.com/chanukyasds/flyway_scripts/main/flyway_deployment.conf'

g=requests.get(git_config_file_url,headers=headers)
print("\nConnected to Git...")

config_dict = ast.literal_eval(g.text)

git_repo = config_dict['git_repo']
git_path = config_dict['git_path']
git_clone_path = config_dict['git_clone_path']
git_clone_command = config_dict['git_clone_command']
flyway_path = config_dict['flyway_path']
flyway_sql_path = config_dict['flyway_sql_path']
flyway_conf_path = config_dict['flyway_conf_path']
git_tree_command = config_dict['git_tree_command']

#find the latest version folder and creating the path

version_dict={}
files_list=os.popen("cd "+git_path+" ; "+git_tree_command)
for i in files_list:
    list = i.split(':')
    version_dict[list[0]]=list[1].replace('\n','')

migration_folder_name=max(version_dict , key=version_dict.get)
migration_folder_time=datetime.fromtimestamp(int(version_dict[migration_folder_name])).strftime('%Y-%m-%d %H:%M:%S')

flyway_version_path = git_clone_path+git_repo+migration_folder_name+'/'

print("\nFound Latest Migration Folder: "+migration_folder_name+" Commited ON "+migration_folder_time)

# pull the latest script from git to repo
print("\nRemoving Old Clone repositories...\n")
os.system("cd "+git_clone_path+" ; rm -rf *")       # remove old repo if exists
os.system("cd "+git_clone_path+" ; "+git_clone_command)  # clone latest repo

# first remove the old script files
#os.system("cd "+flyway_sql_path+" ; "+"rm *.sql")
os.system("cp "+flyway_version_path+"*.sql "+flyway_sql_path)
print("\nFlyway repair processing...")
os.system("cd "+flyway_path+" ; flyway repair")
print("\nFlyway migration processing...")
os.system("cd "+flyway_path+" ; flyway migrate")




