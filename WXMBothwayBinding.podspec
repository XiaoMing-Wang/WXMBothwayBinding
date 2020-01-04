Pod::Spec.new do |s|


  s.name         = "WXMBothwayBinding"
  s.version      = "0.0.3"
  s.summary      = "双向绑定"
  s.description  = <<-DESC
			基于kvo的双向绑定
                   DESC

  s.homepage     = "https://github.com/XiaoMing-Wang/WXMBothwayBinding"
  s.license      = { :type => "MIT", :file => "LICENSE" }

  s.author             = { "wq" => "347511109@qq.com" }
  s.platform     = :ios, "9.0"
  s.source       = { :git => "https://github.com/XiaoMing-Wang/WXMBothwayBinding.git", :tag => "#{s.version}" }

  s.source_files = 'Class'
  #s.public_header_files = 'Class/WXMCategoryHeader.h'

  s.requires_arc = true
  #s.dependency "SDWebImage", "~> 4.4.2"

end
