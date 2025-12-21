add_subdirectory(formatters)

add_subdirectory(environments)

add_library(formattedio STATIC 
	FormatterDecoratorConfigurator.cpp
	FormatterDecorator.cpp
	IOManager.cpp
	)

target_link_libraries(formattedio
	decoratorsio 
	environmentsio
	)
