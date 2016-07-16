#include "ImagePicker.h"
#include "ImagePickerImpl.h"

ImagePicker*  sharedPicker = NULL;

ImagePicker::ImagePicker(){
    _delegate = NULL;
}

ImagePicker* ImagePicker::getInstance(){
    if(sharedPicker == NULL){
        sharedPicker = new ImagePicker();
    }
    return sharedPicker;
}

void ImagePicker::pickImage(ImagePickerDelegate *delegate) {
    _delegate = delegate;
    
    ImagePickerImpl::openImage();
}

void ImagePicker::finishImage(cocos2d::CCTexture2D *image){
    if(_delegate != NULL){
        _delegate->didFinishPickingWithResult(image);
    }
}

//for getNativebackground
void ImagePicker::setDelegate(ImagePickerDelegate *delegate){
    _delegate = delegate;
}