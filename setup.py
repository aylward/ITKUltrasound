from __future__ import print_function
from os import sys

try:
    from skbuild import setup
except ImportError:
    print('scikit-build is required to build from source.', file=sys.stderr)
    print('Please run:', file=sys.stderr)
    print('', file=sys.stderr)
    print('  python -m pip install scikit-build')
    sys.exit(1)

setup(
    name='itk-ultrasound',
    version='0.1.0',
    author='Matthew McCormick',
    author_email='matt.mccormick@kitware.com',
    packages=['itk'],
    package_dir={'itk': 'itk'},
    download_url=r'https://github.com/KitwareMedical/ITKUltrasound',
    description=(r'Filters for use with the Insight Toolkit (ITK)'
        ' that may be particularly useful for the reconstruction and'
        ' analysis of ultrasound images.'),
    long_description=(r'This package contains filters for use with the Insight Toolkit'
        ' (ITK) for the reconstruction and analysis of ultrasound images. This includes'
        ' B-mode image generation, scan conversion, strain imaging, and '
        ' ultrasound spectroscopy.'),
    classifiers=[
        "License :: OSI Approved :: Apache Software License",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Healthcare Industry",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Medical Science Apps.",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Software Development :: Libraries",
        "Operating System :: Android",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS"
        ],
    license='Apache',
    keywords='ITK InsightToolkit ultrasound imaging',
    url=r'http://www.insight-journal.org/browse/publication/722',
    install_requires=[
        r'itk'
    ]
    )
