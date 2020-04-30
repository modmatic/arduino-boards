import hashlib
import json
import os.path
import sys
import tarfile


def make_tarfile(output_filename, source_dir, top_dir):
    with tarfile.open(output_filename, 'w:gz') as tar:
        tar.add(source_dir, arcname=top_dir)

    hasher = hashlib.sha256()
    with open(output_filename, 'rb') as fh:
        data = fh.read()
        hasher.update(data)
        return hasher.hexdigest(), len(data)

def find_version(platform_path):
    with open(platform_path, 'rt') as platform_file:
        for line in platform_file:
            if line.startswith('version='):
                return line.strip('version=').strip()
    return ''

arch = sys.argv[1]

arch_path = os.path.join('..', 'ArduinoCore-' + arch)
platform_path = os.path.join(arch_path, 'platform.txt')
version = find_version(platform_path)
base_url = 'https://https://raw.githubusercontent.com/modmatic/arduino-boards-index/master'
tar_name = 'modmatic-' + arch + '-' + version + '.tar.gz'

# Assumes architecture directory is next to this file's parent directory
digest, size = make_tarfile(tar_name, arch_path, arch)

with open('platform_template.json', 'rt') as platform_template:
    platform = json.load(platform_template)
    with open('package_modmatic_index.json', 'r+') as index_file:
        data = json.load(index_file)
        platform['architecture'] = arch
        platform['version'] = version
        platform['archiveFileName'] = tar_name
        platform['checksum'] = 'SHA-256:' + digest
        platform['size'] = str(size)
        platform['url'] = base_url + '/' + tar_name
        data['packages'][0]['platforms'].append(platform)
        index_file.seek(0)
        json.dump(data, index_file, indent=4, sort_keys=True)
        index_file.truncate()
