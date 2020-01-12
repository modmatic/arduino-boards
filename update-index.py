import hashlib
import json
import os.path
import sys
import tarfile


def make_tarfile(output_filename, source_dir):
    with tarfile.open(output_filename, 'w:gz') as tar:
        tar.add(source_dir, arcname=os.path.basename(source_dir))

    hasher = hashlib.sha256()
    with open(output_filename, 'rb') as fh:
        data = fh.read()
        hasher.update(data)
        return hasher.hexdigest(), len(data)


version = sys.argv[1]
tar_name = 'modmatic-samd-'+version+'.tar.gz'

digest, size = make_tarfile(tar_name, 'samd')

with open('package_modmatic_index.json', 'r+') as index_file:
    data=json.load(index_file)
    for p in data['packages'][0]['platforms']:
        if p['version'] == version:
            p['archiveFileName']=tar_name
            p['checksum']='SHA-256:'+digest
            p['size']=str(size)
            p['url']='file://localhost/Users/andrewmeyer/code/arduino-boards/'+tar_name
            break
    index_file.seek(0)
    json.dump(data, index_file, indent=4, sort_keys=True)
    index_file.truncate()
