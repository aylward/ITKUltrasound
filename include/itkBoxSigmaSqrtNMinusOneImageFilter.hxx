/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkBoxSigmaSqrtNMinusOneImageFilter.hxx,v $
  Language:  C++
  Date:      $Date: 2008-08-10 13:00:06 $
  Version:   $Revision: 1.3 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef itkBoxSigmaSqrtNMinusOneImageFilter_hxx
#define itkBoxSigmaSqrtNMinusOneImageFilter_hxx

#include "itkImage.h"
#include "itkBoxSigmaSqrtNMinusOneImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkOffset.h"
#include "itkProgressAccumulator.h"
#include "itkNumericTraits.h"
#include "itkNeighborhoodAlgorithm.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkBoxUtilities.h"

namespace itk {


template<class TInputImage, class TOutputImage>
BoxSigmaSqrtNMinusOneImageFilter<TInputImage, TOutputImage>
::BoxSigmaSqrtNMinusOneImageFilter()
{
}


template<class TInputImage, class TOutputImage>
void
BoxSigmaSqrtNMinusOneImageFilter<TInputImage, TOutputImage>
::ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, int threadId) 
{

  // Accumulate type is too small
  typedef typename itk::NumericTraits<PixelType>::RealType             AccValueType;
  typedef typename itk::Vector<AccValueType, 2>                        AccPixType;
  typedef typename itk::Image<AccPixType, TInputImage::ImageDimension> AccumImageType;

  typename TInputImage::SizeType internalRadius;
  for( int i=0; i<TInputImage::ImageDimension; i++ )
    {
    internalRadius[i] = this->GetRadius()[i] + 1;
    }
  

  const InputImageType* inputImage = this->GetInput();
  OutputImageType *outputImage = this->GetOutput();
  RegionType accumRegion = outputRegionForThread;
  accumRegion.PadByRadius(internalRadius);
  accumRegion.Crop(inputImage->GetRequestedRegion());

  ProgressReporter progress(this, threadId, 2*accumRegion.GetNumberOfPixels());

  typename AccumImageType::Pointer accImage = AccumImageType::New();
  accImage->SetRegions(accumRegion);
  accImage->Allocate();

  BoxSquareAccumulateFunction<TInputImage, AccumImageType >(inputImage, accImage, 
                                                     accumRegion,
                                                     accumRegion,
                                                     progress);
  BoxSigmaSqrtNMinusOneCalculatorFunction<AccumImageType, TOutputImage>(accImage, outputImage,
                                                          accumRegion,
                                                          outputRegionForThread,
                                                          this->GetRadius(),
                                                          progress);
}


}// end namespace itk

#endif
