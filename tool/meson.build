tinyxml2 = dependency('tinyxml2')
libarchive = dependency('libarchive')
libcurl = dependency('libcurl')
libssl = dependency('libssl')
libcrypto = dependency('libcrypto')
curlpp = dependency('curlpp')
boost = dependency('boost', modules : ['filesystem'])

git_version = run_command(['git', 'rev-parse', '--short', 'HEAD'], capture : true, check : true).stdout().strip()
compile_date = run_command(['date', '+%Y%m%d-%H%M'], capture : true, check : true).stdout().strip()
scrape_username = run_command(['printenv', 'SCRAPE_USERNAME'], capture : true, check : true).stdout().strip()
scrape_password = run_command(['printenv', 'SCRAPE_PASSWORD'], capture : true, check : true).stdout().strip()
scrape_url = run_command(['printenv', 'SCRAPE_URL'], capture : true, check : true).stdout().strip()

conf_data = configuration_data()
conf_data.set('GIT_VERSION', '"'+git_version+'"')
conf_data.set('COMPILE_DATE', '"'+compile_date+'"') 
conf_data.set('SCRAPE_USERNAME', '"'+scrape_username+'"')
conf_data.set('SCRAPE_PASSWORD', '"'+scrape_password+'"') 
conf_data.set('SCRAPE_URL', '"'+scrape_url+'"') 
configure_file(
  output : 'config.h',
  configuration : conf_data
)

exe = executable(
  'pandorytool', 
  sources: [
    'main.cpp',
    'src/PandoryTool.cpp',
    'src/CommandLineArguments.cpp',
    'src/EditionCheck.cpp',
    'src/modes/ModeAdd.cpp',
    'src/modes/ModePrepare.cpp',
    'src/modes/ModePspfix.cpp',
    'src/Fs.cpp',
    'src/modes/ModeStick.cpp',
    'src/ScrapeService.cpp',
    'src/Hash.cpp',
    'src/McGamesAbstract.cpp',
    'src/SystemMapper.cpp',
    'src/McGamesTXT.cpp',
    'src/McGamesXML.cpp',
    'src/ScreenScraperXML.cpp',
    'src/definitions/DXPatches.cpp',
    'src/definitions/PSPMapper.cpp',
    'src/UserFolders.cpp',
    'src/definitions/Sticks.cpp',
    'src/StickDownloader.cpp',
    'src/StickExtractor.cpp',
    'src/modes/ModeJailbreakStick.cpp',
    'src/modes/ModeDXStick.cpp',
    'src/ScreenScraper.cpp',
    'src/SystemDefinition.cpp',
  ],
  include_directories: 'include',
  dependencies : [tinyxml2, libarchive, libcurl, curlpp, libssl, libcrypto, boost],
  install : true
)

test('basic', exe)